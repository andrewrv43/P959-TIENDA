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
    QStringList cabecera={"Cantidad","Producto","SubTotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
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

