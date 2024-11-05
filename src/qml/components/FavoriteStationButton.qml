import Radio.Favorites

IconButton {
    required property var station

    property bool favorited: FavoritesManager.favorites.includes(station)

    icon.source: `qrc:/assets/icons/${(favorited) ? "favorited" : "favorite"}Icon.svg`

    toolTip: (favorited) ? "Remove from Favorites" : "Add to Favorites"

    enabled: station.streamUrls.length !== 0

    onClicked: ((favorited) ? FavoritesManager.removeStation : FavoritesManager.addStation)(
                   station)
}
