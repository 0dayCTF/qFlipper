import QtQuick 2.15
import QtQuick.Window 2.15

import "components"

Window {
    id: root
    visible: true
    flags: Qt.Window | Qt.FramelessWindowHint | Qt.NoDropShadowWindowHint
    title: Qt.application.displayName

    height: mainWindow.baseHeight + mainWindow.shadowSize * 2

    minimumWidth: mainWindow.baseWidth + mainWindow.shadowSize * 2
    minimumHeight: mainWindow.baseHeight + mainWindow.shadowSize * 2

    maximumWidth: minimumWidth
    maximumHeight: minimumHeight

    color: "transparent"

    DragHandler {
        onActiveChanged: if(active) { root.startSystemMove(); }
        target: null
    }

    MainWindow {
        id: mainWindow

        onExpandStarted: {
            root.maximumHeight = baseHeight + logHeight + shadowSize * 2;
            root.height = root.maximumHeight;
        }

        onExpandFinished: {
            root.minimumHeight = root.maximumHeight;
        }

        onCollapseStarted: {
            root.minimumHeight = baseHeight + shadowSize * 2;
        }

        onCollapseFinished: {
            root.height = root.minimumHeight;
            root.maximumHeight = root.minimumHeight;
        }

        onResizeStarted: {
            root.maximumHeight = root.Screen.height - root.y;
            root.height = root.maximumHeight;
        }

        onResizeFinished: {
            root.height = mainWindow.height + mainWindow.shadowSize * 2;
            root.maximumHeight = root.height;
            root.minimumHeight = root.height;
        }
    }

    Component.onCompleted: {
        mainWindow.controls.minimizeRequested.connect(root.showMinimized);
        mainWindow.controls.closeRequested.connect(Qt.quit);
    }
}
