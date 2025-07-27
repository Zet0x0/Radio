function zeroPad(n) {
    return n.toString().padStart(2, "0");
}

function showMessageDialog(applicationWindow, title, message, exitOnClose) {
    var component = Qt.createComponent("Radio.Shared", "MessageDialog", Component.PreferSynchronous, applicationWindow);

    if (component.status !== Component.Ready) {
        return;
    }

    var dialog = component.createObject(applicationWindow, {
        title: title,
        message: message,
        exitOnClose: exitOnClose
    });

    dialog.open();

    applicationWindow.show();
    applicationWindow.requestActivate();
}
