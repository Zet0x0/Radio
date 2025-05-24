import Radio.MainWindow
import Radio.SystemTray

MainWindow {
    id: applicationWindow

    SystemTrayIcon {
        applicationWindow: applicationWindow

        systemTrayMenu: SystemTrayMenu {
        }
    }
}
