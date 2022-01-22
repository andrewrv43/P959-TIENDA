#include "finalizacion.h"
#include "ui_finalizacion.h"

Finalizacion::Finalizacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finalizacion)
{
    ui->setupUi(this);
}

Finalizacion::~Finalizacion()
{
    delete ui;
}



Ui::Finalizacion *Finalizacion::getUi() const
{
    return ui;
}

void Finalizacion::setUi(Ui::Finalizacion *newUi)
{
    ui = newUi;
}

const QString &Finalizacion::detalles() const
{
    return m_detalles;
}

const QString &Finalizacion::nombre() const
{
    return m_nombre;
}

void Finalizacion::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

const QString &Finalizacion::cedula() const
{
    return m_cedula;
}

void Finalizacion::setCedula(const QString &newCedula)
{
    m_cedula = newCedula;
}

const QString &Finalizacion::mail() const
{
    return m_mail;
}

void Finalizacion::setMail(const QString &newMail)
{
    m_mail = newMail;
}

const QString &Finalizacion::telefono() const
{
    return m_telefono;
}

void Finalizacion::setTelefono(const QString &newTelefono)
{
    m_telefono = newTelefono;
}

const QString &Finalizacion::direccion() const
{
    return m_direccion;
}

void Finalizacion::setDireccion(const QString &newDireccion)
{
    m_direccion = newDireccion;
}

void Finalizacion::insertarDatos(QString nombre, QString cedula, QString telef, QString mail, QString direccion)
{
    setNombre(nombre);
    setCedula(cedula);
    setTelefono(telef);
    setMail(mail);
    setDireccion(direccion);
    presentacion();
}

void Finalizacion::presentacion()
{
    QString encabezado="\t-------------------------------------------------------------\n\t\tABARROTES SANDY\n"
                       "\t-------------------------------------------------------------\n"
                       "RUC: 9999999999\n"
                       "Direccion: Av. y Av. Rumichaca Ñan, Av. Moran Valverde\nQuito 170146\n"
                       "Numero: (02) 396-2800\n"
                       "\t---------------------------------------------------------\n"
                       "\t\t      CLIENTE\n"
                       "\t---------------------------------------------------------\n";

    QString name="Nombre: "+m_nombre+"\n";
    QString cedula="Cedula: "+m_cedula+"\n";
    QString telef="Telefono: "+m_telefono+"\n";
    QString mail="E-Mail: "+m_mail+"\n";
    QString direc="Direccion: "+m_direccion+"\n";

    QString data=encabezado+name+cedula+telef+mail+direc;
    ui->outDatos->setPlainText(data);
}


