#ifndef FINALIZACION_H
#define FINALIZACION_H

#include <QDialog>

namespace Ui {
class Finalizacion;
}

class Finalizacion : public QDialog
{
    Q_OBJECT

public:
    explicit Finalizacion(QWidget *parent = nullptr);
    ~Finalizacion();

    void setDetalles(const QString &newDetalles);

    Ui::Finalizacion *getUi() const;
    void setUi(Ui::Finalizacion *newUi);
    const QString &detalles() const;
    const QString &nombre() const;
    void setNombre(const QString &newNombre);
    const QString &cedula() const;
    void setCedula(const QString &newCedula);
    const QString &mail() const;
    void setMail(const QString &newMail);
    const QString &telefono() const;
    void setTelefono(const QString &newTelefono);
    const QString &direccion() const;
    void setDireccion(const QString &newDireccion);
    void insertarDatos(QString nombre,QString cedula,
                       QString telef,QString mail,QString direccion,QString detalles);

private:
    Ui::Finalizacion *ui;
    QString m_detalles;
    QString m_nombre;
    QString m_cedula;
    QString m_mail;
    QString m_telefono;
    QString m_direccion;
    void presentacion();

};

#endif // FINALIZACION_H
