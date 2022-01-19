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

bool Tienda::verificarCedula(QString as)
{
    if(as=="1722225461"){
        return true;
    }
    else{
        return false;
    }
}

void Tienda::checkVacios()
{
    //verificar si estan correctos o vacios para pintar el background
    //cedula
    if(verificarCedula(ui->inCedula->text())==false){
        QPalette palette=ui->inCedula->palette();
        palette.setColor(ui->inCedula->backgroundRole(),Qt::red);
        palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
        ui->inCedula->setPalette(palette);

    }
    else{
        QPalette palette=ui->inCedula->palette();
        palette.setColor(ui->inCedula->backgroundRole(),Qt::green);
        palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
        ui->inCedula->setPalette(palette);
    }
    //nombre
    if(ui->inNom->text().isEmpty()){
        QPalette palette=ui->inNom->palette();
        palette.setColor(ui->inNom->backgroundRole(),Qt::red);
        palette.setColor(ui->inNom->foregroundRole(),Qt::black);
        ui->inNom->setPalette(palette);
    }
    else{
        QPalette palette=ui->inNom->palette();
        palette.setColor(ui->inNom->backgroundRole(),Qt::green);
        palette.setColor(ui->inNom->foregroundRole(),Qt::black);
        ui->inNom->setPalette(palette);
    }
    //telefono
    if(ui->inTelf->text().isEmpty()){
        QPalette palette=ui->inTelf->palette();
        palette.setColor(ui->inTelf->backgroundRole(),Qt::red);
        palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
        ui->inTelf->setPalette(palette);
    }
    else{
        QPalette palette=ui->inTelf->palette();
        palette.setColor(ui->inTelf->backgroundRole(),Qt::green);
        palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
        ui->inTelf->setPalette(palette);
    }
    //email
    if(ui->inMail->text().isEmpty()){
        QPalette palette=ui->inMail->palette();
        palette.setColor(ui->inMail->backgroundRole(),Qt::red);
        palette.setColor(ui->inMail->foregroundRole(),Qt::black);
        ui->inMail->setPalette(palette);
    }
    else{
        QPalette palette=ui->inMail->palette();
        palette.setColor(ui->inMail->backgroundRole(),Qt::green);
        palette.setColor(ui->inMail->foregroundRole(),Qt::black);
        ui->inMail->setPalette(palette);
    }
    //direccion
    if(ui->inDireccion->toPlainText().isEmpty()){
        QPalette palette=ui->inDireccion->palette();
        palette.setColor(ui->inDireccion->backgroundRole(),Qt::red);
        palette.setColor(ui->inDireccion->foregroundRole(),Qt::red);
        ui->inDireccion->setPalette(palette);
    }
    else{
        QPalette palette=ui->inDireccion->palette();
        palette.setColor(ui->inDireccion->backgroundRole(),Qt::green);
        palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
        ui->inDireccion->setPalette(palette);
    }
}

void Tienda::backgroundReset()
{
    //CEDULA
    QPalette palette=ui->inCedula->palette();
    palette.setColor(ui->inCedula->backgroundRole(),Qt::white);
    palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
    ui->inCedula->setPalette(palette);
    //NOMBRE
    palette=ui->inNom->palette();
    palette.setColor(ui->inNom->backgroundRole(),Qt::white);
    palette.setColor(ui->inNom->foregroundRole(),Qt::black);
    ui->inNom->setPalette(palette);
    //TELEFONO
    palette=ui->inTelf->palette();
    palette.setColor(ui->inTelf->backgroundRole(),Qt::white);
    palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
    ui->inTelf->setPalette(palette);
    //E-MAIL
    palette=ui->inMail->palette();
    palette.setColor(ui->inMail->backgroundRole(),Qt::white);
    palette.setColor(ui->inMail->foregroundRole(),Qt::black);
    ui->inMail->setPalette(palette);
    //DIRECCION
    palette=ui->inDireccion->palette();
    palette.setColor(ui->inDireccion->backgroundRole(),Qt::white);
    palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
    ui->inDireccion->setPalette(palette);



}

void Tienda::clearIn()
{
    ui->inNom->clear();
    ui->inCedula->clear();
    ui->inTelf->clear();
    ui->inDireccion->clear();
    ui->inMail->clear();
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


void Tienda::on_pushButton_released()
{
    bool condition=false;
    checkVacios();
    if(ui->inNom->text().isEmpty()||verificarCedula(ui->inCedula->text())==false){
     ui->statusbar->showMessage("Datos erroneos!",3500);
        condition=false;
    }
    else{
         ui->statusbar->showMessage("Confirme los datos ingresados",3500);
        condition=true;

    }
    if(condition==true){
        Finalizacion *finalizar =new Finalizacion(this);
        //agregar variables
        //nombre
        finalizar->insertarDatos(ui->inNom->text(),ui->inCedula->text()
                                 ,ui->inTelf->text(),ui->inMail->text()
                                 ,ui->inDireccion->toPlainText());
        finalizar->exec();
        clearIn();
        backgroundReset();
    }
}

