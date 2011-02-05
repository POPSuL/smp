#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtGui/QMessageBox>

#define ERRM(Msg) QMessageBox::critical(0, "Error", Msg)

#define DBG /*dbg*/


#ifdef DBG
#include <QDebug>
#endif //DBG
#endif // GLOBAL_H
