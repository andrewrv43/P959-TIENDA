#include "finalizacion.h"
#include "ui_finalizacion.h"

Finalizacion::Finalizacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finalizacion)
{
    ui->setupUi(this);
    m_acept=false;
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

void Finalizacion::insertarDatos(QString nombre, QString cedula, QString telef, QString mail, QString direccion, QString detalles)
{
    setNombre(nombre);
    setCedula(cedula);
    setTelefono(telef);
    setMail(mail);
    setDireccion(direccion);
    m_detalles=detalles;
    presentacion();
}

void Finalizacion::presentacion()
{
    QString data="";
    QString encabezado="\t-------------------------------------------------------------\n\t\tABARROTES SANDY\n"
                       "\t-------------------------------------------------------------\n"
                       "\tRUC: 9999999999\n"
                       "\tDireccion: Av. y Av. Rumichaca Ñan, Av. Moran \n\tValverde Quito 170146\n"
                       "\tNumero: (02) 396-2800\n"
                       "\t---------------------------------------------------------\n"
                       "\t\t      CLIENTE\n"
                       "\t---------------------------------------------------------\n";
  data=encabezado;
    if(m_cedula!="9999999999"){
        QString name="\tNombre: "+m_nombre+"\n";
        QString cedula="\tCedula: "+m_cedula+"\n";
        QString telef="\tTelefono: "+m_telefono+"\n";
        QString mail="\tE-Mail: "+m_mail+"\n";
        QString direc="\tDireccion: "+m_direccion+"\n"
                                                "\t---------------------------------------------------------\n";
        data+=name+cedula+telef+mail+direc+"\n"+"\n";
    }
    else{
        QString add="\t\tCONSUMIDOR FINAL\n\n\t---------------------------------------------------------\n";
        data+=add;
    }
    QString pro;
    pro="\tCant.\tProducto\tP.Unitario\tSubTotal\n"+m_detalles;

    data+=pro;

    ui->outDatos->setPlainText(data);
    calculosString();
}

void Finalizacion::generacion()
{
    QFile archivo("Generador.txt");
    if(archivo.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream datosArchivo(&archivo);
                datosArchivo<<ui->outDatos->toPlainText();
    }
    archivo.close();
}

void Finalizacion::calculosString()
{
    QString Subtotales="";
    float iva=m_subtotal*m_iva/100;
    Subtotales="\t-------------------------------------------------------------\n"
               "\t\t\tSubTotal:\t"+QString::number(m_subtotal,'f',2)+"\n"
               "\t\t\tIVA"+QString::number(m_iva,'f',2)+"%:\t"+QString::number(iva,'f',2)+"\n"
               "\t\t\tTOTAL:\t"+QString::number(m_subtotal+iva,'f',2);
    ui->outDatos->appendPlainText(Subtotales);

}

void Finalizacion::setIva(int newIva)
{
    m_iva = newIva;
}

void Finalizacion::setSubtotal(float newSubtotal)
{
    m_subtotal = newSubtotal;
}

float Finalizacion::subtotal() const
{
    return m_subtotal;
}



void Finalizacion::on_buttonBox_accepted()
{
    m_acept=true;
    generacion();
}


void Finalizacion::on_buttonBox_rejected()
{
    //eliminar datos

}

