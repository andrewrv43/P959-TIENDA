#include "tienda.h"
#include "ui_tienda.h"

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);

    //lista de productos
    cargarProductos();
    //mostrar productos en el combo
    foreach(Producto *p, m_productos){
        ui->inNombre->addItem(p->nombre());
    }
    //configurar cabecera de la tabla
    QStringList cabecera={"Cantidad","Producto","P.Unitario","SubTotal"};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    m_subtotal=0;
}

Tienda::~Tienda()
{

    delete ui;
}
/**
 * @brief Tienda::cargarProductos Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    //crear productos quemados en el codigo
    m_productos.append(new Producto(1,"Leche",0.80));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.50));
    //podria leerse de una base de datos, archivos, incluso de internet
}

void Tienda::calcular(float subtotal)
{
    m_subtotal+=subtotal;
    float iva=m_subtotal*IVA/100;
    float total=m_subtotal+iva;
    ui->outSubtotal_13->setText("$ "+QString::number(m_subtotal,'f',2));
    ui->outIva->setText("$ "+QString::number(iva,'f',2));
    ui->outTotal->setText("$ "+QString::number(total,'f',2));
}


void Tienda::on_inNombre_currentIndexChanged(int index)
{
    float precio = m_productos.at(index)->precio();
    ui->outPrecio->setText(QString::number(precio,'f',2));
    ui->inCantidad->setValue(0);
}


void Tienda::on_btnAgregar_released()
{
    //validar que no se agreguen productos con 0 cantidad
    int cantidad= ui->inCantidad->value();
    if(cantidad==0){
        return;
    }
    int i=ui->inNombre->currentIndex();
    Producto *p =m_productos.at(i);

    float subtotal=p->precio()*cantidad;
    //agregar datos a la tabla
    int fila= ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad,'f',2)));
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(p->precio(),'f',2)));
    ui->outDetalle->setItem(fila,3,new QTableWidgetItem(QString::number(subtotal,'f',2)));

    //limpiar
    ui->inCantidad->setValue(0);
    ui->inNombre->setFocus();

    //calculos
    calcular(subtotal);

}

