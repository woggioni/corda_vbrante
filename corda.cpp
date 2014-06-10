#include <QtGui>
#include "corda.hpp"

int core( val_t v, val_t len, val_t durata, memory_storage m);

corda::corda(QWidget* parent)
    : QWidget(parent) //wavfile("y.wav")
{
	setupUi(this);
    //memory_storage m();
	v=316.228;
	connect(densitaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(reset(void)));
	connect(tensioneSpinBox, SIGNAL(valueChanged(double)), this, SLOT(reset(void)));
	connect(WAV_Button, SIGNAL(clicked()), this, SLOT(generate_WAV(void)));
    connect(playButton, SIGNAL(clicked()), this, SLOT(play(void)));
	connect(WAV_Button, SIGNAL(clicked()), this, SLOT(en_play(void)));
	connect(densitaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(dis_play(void)));
	connect(tensioneSpinBox, SIGNAL(valueChanged(double)), this, SLOT(dis_play(void)));
	connect(lunghezzaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(dis_play(void)));
	connect(lunghezzaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(reset(void)));
	connect(tensioneSlider, SIGNAL(valueChanged(int)), this, SLOT(up_tensione_spinbox()));
	connect(tensioneSpinBox, SIGNAL(valueChanged(double)), this, SLOT(up_tensione_slider()));
	connect(lunghezzaSlider, SIGNAL(valueChanged(int)), this, SLOT(up_lunghezza_spinbox()));
	connect(lunghezzaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(up_lunghezza_slider()));
	connect(densitaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(up_densita_slider()));
	connect(densitaSlider, SIGNAL(valueChanged(int)), this, SLOT(up_densita_spinbox()));
    connect(durataSpinBox, SIGNAL(valueChanged(double)), SLOT(dis_play()));
    connect(durataSpinBox, SIGNAL(valueChanged(double)), this, SLOT(up_durata_slider()));
    connect(durataSlider, SIGNAL(valueChanged(int)), this, SLOT(up_durata_spinbox()));
}

void corda::reset(void)
{
	v=sqrt(1000*tensioneSpinBox->value()/densitaSpinBox->value());
	velocitadisp->setNum(v);
	frequenzadisp->setNum(v/2/lunghezzaSpinBox->value());
}

void corda::generate_WAV(void)
{
	core( v, lunghezzaSpinBox->value(), durataSpinBox->value(), m);
	cout << lunghezzaSpinBox->value() << '\t' << v << "\t" <<durataSpinBox->value() << endl;
}

void corda::play(void)
{
    system("play y.wav");
    //wavfile.play("y.wav");
}

void corda::en_play(void)
{
	playButton->setEnabled(1);
}

void corda::dis_play(void)
{
	playButton->setEnabled(0);
}

void corda::up_tensione_spinbox(void)
{
tensioneSpinBox->setValue(roundf(pow(10,(tensioneSlider->value()/10.0))));
}

void corda::up_tensione_slider(void)
{
tensioneSlider->setValue(int(roundf(10*log10(tensioneSpinBox->value()))));
}

void corda::up_lunghezza_spinbox(void)
{
	lunghezzaSpinBox->setValue(lunghezzaSlider->value()/100.0);
}

void corda::up_lunghezza_slider(void)
{
	lunghezzaSlider->setValue(lunghezzaSpinBox->value()*100.0);
}

void corda::up_densita_slider(void)
{
	densitaSlider->setValue(densitaSpinBox->value());
}
void corda::up_densita_spinbox(void)
{
	densitaSpinBox->setValue(densitaSlider->value());
}

void corda::up_durata_spinbox(void)
{
    durataSpinBox->setValue(durataSlider->value()/10);
}

void corda::up_durata_slider(void)
{
    durataSlider->setValue(durataSpinBox->value()*10);
}
