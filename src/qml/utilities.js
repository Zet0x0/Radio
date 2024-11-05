.import Radio.CppUtilities 1.0 as CppUtilities

function modelDataToStation(modelData) {
    const streamUrls = modelData.streamUrls

    return CppUtilities.CppUtilities.stationFromJson({
                                                         "streamUrls": Object.keys(
                                                                           streamUrls).map(
                                                                           key => streamUrls[key]),
                                                         "imageUrl": modelData.imageUrl,
                                                         "subtitle": modelData.subtitle,
                                                         "title": modelData.title
                                                     })
}

function dedent(string) {
    return string.replace(/^ +/gm, "")
}
