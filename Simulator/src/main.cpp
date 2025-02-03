#include <QApplication>
#include <QDialog>
#include <QDir>
#include <QLibrary>
#include <QSystemTrayIcon>
#include <QTextStream>
#include <iostream>

#include "MainWindow.h"

auto LoadDll(const QString& dllName, int& argc, char** argv) -> int {
	if (QLibrary::isLibrary(dllName)) {
		QLibrary lib(dllName);
		lib.load();
		if (!lib.isLoaded()) {
			std::cerr << "Could not load library:" << lib.errorString().toStdString() << std::endl;
			return -1;
		} else {
			std::cout << "Library loaded successfully" << std::endl;
		}
	}

	return 0;
}

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	StealthApp w;

	return a.exec();
}
