import Radio.MainWindow
import Radio.SystemTray

MainWindow {
    id: applicationWindow

    SystemTrayIcon {
        systemTrayMenu: SystemTrayMenu {
            applicationWindow: applicationWindow
        }
    }
}
