# PyQt5入门
## 基础
模块
* QtCore
* QtGui
* QtWidgets
* QtMultimedia
* QtBluetooth
* QtNetwork
* QtPositioning
* Enginio
* QtWebSockets
* QtWebKit
* QtWebKitWidgets
* QtXml
* QtSvg
* QtSql
* QtTest

1. 简单的窗口
```python3
import sys
from PyQt5.QtWidgets import QApplication, QWidget

def show_w():
	app = QApplication(sys.argv)
	
	w = QWidget()
	
	w.resize(500, 500)
	w.move(500, 100)
	w.setWindowTitle('Simple')
	w.show()
	
	sys.exit(app.exec_())
	# sys.exit()
	
if __name__ == '__main__':
	show_w()
```

2. 应用图标，按钮，窗口关闭
```python3
import sys
from PyQt5.QtWidgets import (QWidget, QToolTip, QDesktopWidget, QMessageBox, QTextEdit, QLabel, QPushButton, QApplication, QMainWindow,QAction, qApp, QHboxLayout, QVBoxLayout, QGridLayout,QLineEdit)
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtCore import QCoreApplication

class AppIcon(QWidget):
	def __init__(self):
		super().__init__()
		self.initUI()
	
	def initUI(self):
		
```

```shell
export PATH="./.local/lib/python3.9/site-packages/qt5_applications/Qt/bin/$PATH" 
```