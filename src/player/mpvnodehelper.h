#pragma once

#include <QVariant>
#include <mpv/client.h>

/*
 * https://github.com/mpv-player/mpv-examples/blob/e0d1a84c99e8c469b58fde31a1541401acfb0eb2/libmpv/common/qthelper.hpp#L78-L195
 */
struct MpvNodeBuilder
{
    MpvNodeBuilder(const QVariant &);
    ~MpvNodeBuilder();

    mpv_node *node();

private:
    Q_DISABLE_COPY(MpvNodeBuilder)

    mpv_node m_node;

    char *duplicateQString(const QString &);
    bool testType(const QVariant &, const QMetaType::Type &);

    mpv_node_list *
        createNodeList(mpv_node *, const bool &isMap, const int &size);
    void set(mpv_node *, const QVariant &value);

    void freeNode(mpv_node *);
};

/*
 * https://github.com/mpv-player/mpv-examples/blob/e0d1a84c99e8c469b58fde31a1541401acfb0eb2/libmpv/common/qthelper.hpp#L200-L204
 */
struct MpvNodeAutoFree
{
    mpv_node *node;

    MpvNodeAutoFree(mpv_node *);
    ~MpvNodeAutoFree();
};

/*
 * https://github.com/mpv-player/mpv-examples/blob/e0d1a84c99e8c469b58fde31a1541401acfb0eb2/libmpv/common/qthelper.hpp#L46-L76
 */
QVariant nodeToVariant(const mpv_node *node);
