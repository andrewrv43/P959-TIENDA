#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <producto.h>
#include <QDebug>
#define IVA 12
QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();

private slots:
    void on_inNombre_currentIndexChanged(int index);

    void on_btnAgregar_released();

private:
    Ui::Tienda *ui;
    QList<Producto*>m_productos;
    void cargarProductos();
    float m_subtotal;
    void calcular(float subtotal);
};
#endif // TIENDA_H
