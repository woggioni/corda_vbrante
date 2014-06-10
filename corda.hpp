#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H
#include <QDialog>
#include <QSound>
#include "ui_corda.h"
#include "core.hpp"

class corda : public QWidget, public Ui_Form
{
Q_OBJECT
public:
corda(QWidget *parent = 0);
//QSound wavfile;
double v;
memory_storage m;
private slots:
void reset(void);
void generate_WAV(void);
void play(void);
void en_play(void);
void dis_play(void);
void up_tensione_spinbox(void);
void up_tensione_slider(void);
void up_lunghezza_spinbox(void);
void up_lunghezza_slider(void);
void up_densita_slider(void);
void up_densita_spinbox(void);
void up_durata_spinbox(void);
void up_durata_slider(void);
};
#endif

