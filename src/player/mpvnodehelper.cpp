#include "mpvnodehelper.h"

MpvNodeBuilder::MpvNodeBuilder(const QVariant &value)
{
    set(&m_node, value);
}

MpvNodeBuilder::~MpvNodeBuilder()
{
    freeNode(&m_node);
}

mpv_node *MpvNodeBuilder::node()
{
    return &m_node;
}

char *MpvNodeBuilder::duplicateQString(const QString &qString)
{
    QByteArray byteArray = qString.toUtf8();

    char *string = new char[byteArray.size() + 1];

    if (string)
    {
        std::memcpy(string, byteArray.data(), byteArray.size() + 1);
    }

    return string;
}

bool MpvNodeBuilder::testType(const QVariant &value,
                              const QMetaType::Type &type)
{
    return value.typeId() == type;
}

mpv_node_list *MpvNodeBuilder::createNodeList(mpv_node *node,
                                              const bool &isMap,
                                              const int &size)
{
    node->format = (isMap) ? MPV_FORMAT_NODE_MAP : MPV_FORMAT_NODE_ARRAY;

    mpv_node_list *list = new mpv_node_list();
    node->u.list = list;

    if (!list)
    {
        goto error;
    }

    list->values = new mpv_node[size]();

    if (!list->values)
    {
        goto error;
    }

    if (isMap)
    {
        list->keys = new char *[size]();

        if (!list->keys)
        {
            goto error;
        }
    }

    return list;

error:
    freeNode(node);

    return NULL;
}

void MpvNodeBuilder::set(mpv_node *node, const QVariant &value)
{
    if (testType(value, QMetaType::QString))
    {
        node->format = MPV_FORMAT_STRING;
        node->u.string = duplicateQString(value.toString());

        if (!node->u.string)
        {
            goto fail;
        }
    }
    else if (testType(value, QMetaType::Bool))
    {
        node->format = MPV_FORMAT_FLAG;
        node->u.flag = value.toBool() ? 1 : 0;
    }
    else if (testType(value, QMetaType::Int)
             || testType(value, QMetaType::LongLong)
             || testType(value, QMetaType::UInt)
             || testType(value, QMetaType::ULongLong))
    {
        node->format = MPV_FORMAT_INT64;
        node->u.int64 = value.toLongLong();
    }
    else if (testType(value, QMetaType::Double))
    {
        node->format = MPV_FORMAT_DOUBLE;
        node->u.double_ = value.toDouble();
    }
    else if (value.canConvert<QVariantList>())
    {
        QVariantList qList = value.toList();
        mpv_node_list *nodeList = createNodeList(node, false, qList.size());

        if (!nodeList)
        {
            goto fail;
        }

        nodeList->num = qList.size();

        for (int i = 0; i < qList.size(); i++)
        {
            set(&nodeList->values[i], qList[i]);
        }
    }
    else if (value.canConvert<QVariantMap>())
    {
        QVariantMap qMap = value.toMap();
        mpv_node_list *nodeList = createNodeList(node, true, qMap.size());

        if (!nodeList)
        {
            goto fail;
        }

        nodeList->num = qMap.size();

        for (int i = 0; i < qMap.size(); i++)
        {
            nodeList->keys[i] = duplicateQString(qMap.keys()[i]);

            if (!nodeList->keys[i])
            {
                freeNode(node);

                goto fail;
            }

            set(&nodeList->values[i], qMap.values()[i]);
        }
    }
    else
    {
        goto fail;
    }

    return;

fail:
    node->format = MPV_FORMAT_NONE;
}

void MpvNodeBuilder::freeNode(mpv_node *node)
{
    switch (node->format)
    {
        case MPV_FORMAT_STRING:
        {
            delete[] node->u.string;

            break;
        }

        case MPV_FORMAT_NODE_ARRAY:
        case MPV_FORMAT_NODE_MAP:
        {
            mpv_node_list *list = node->u.list;

            if (list)
            {
                for (int i = 0; i < list->num; i++)
                {
                    if (list->keys)
                    {
                        delete[] list->keys[i];
                    }

                    if (list->values)
                    {
                        freeNode(&list->values[i]);
                    }
                }

                delete[] list->keys;
                delete[] list->values;
            }

            delete list;

            break;
        }

        default:
        {
            break;
        }
    }

    node->format = MPV_FORMAT_NONE;
}

MpvNodeAutoFree::MpvNodeAutoFree(mpv_node *node)
    : node(node)
{
}

MpvNodeAutoFree::~MpvNodeAutoFree()
{
    mpv_free_node_contents(node);
}

QVariant nodeToVariant(const mpv_node *node)
{
    switch (node->format)
    {
        case MPV_FORMAT_STRING:
        {
            return QString::fromUtf8(node->u.string);
        }

        case MPV_FORMAT_FLAG:
        {
            return static_cast<bool>(node->u.flag);
        }

        case MPV_FORMAT_INT64:
        {
            return static_cast<qlonglong>(node->u.int64);
        }

        case MPV_FORMAT_DOUBLE:
        {
            return node->u.double_;
        }

        case MPV_FORMAT_NODE_ARRAY:
        {
            mpv_node_list *nodeList = node->u.list;
            QVariantList qList;

            for (int i = 0; i < nodeList->num; i++)
            {
                qList.append(nodeToVariant(&nodeList->values[i]));
            }

            return qList;
        }

        case MPV_FORMAT_NODE_MAP:
        {
            mpv_node_list *nodeList = node->u.list;
            QVariantMap qMap;

            for (int n = 0; n < nodeList->num; n++)
            {
                qMap.insert(QString::fromUtf8(nodeList->keys[n]),
                            nodeToVariant(&nodeList->values[n]));
            }

            return qMap;
        }

        default: // MPV_FORMAT_NONE, unknown values (e.g. future extensions)
        {
            return QVariant();
        }
    }
}
