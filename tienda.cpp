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
    m_details="";
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

void Tienda::calcular()
{
    int fila=ui->outDetalle->rowCount();
    int contador=0;
    float sumatoria=0;
    while(contador!=fila){
        sumatoria+=ui->outDetalle->item(contador,3)->text().toDouble();
        contador++;
    }
    m_subtotal=sumatoria;


    float iva=m_subtotal*IVA/100;
    float total=m_subtotal+iva;
    ui->outSubtotal_13->setText("$ "+QString::number(m_subtotal,'f',2));
    ui->outIva->setText("$ "+QString::number(iva,'f',2));
    ui->outTotal->setText("$ "+QString::number(total,'f',2));
}

bool Tienda::verificarCedula(QString as)
{
    bool est = true;
    int vcedula[10];
    int vPar[4];
    int vImpar[5]={0};
    int sumaPar=0;
    int sumaImpar=0;
    int total;
    int nveri;

    double nu;

    if(as=="9999999999"){
        return true;
    }

    do
    {

        nu=as.toInt();
        if(nu<100000000 || nu>9999999999)
        {

            est=false;
            break;
        }


        //Separar string
        QString p1=as.mid(0,1);
        QString p2=as.mid(1,1);
        QString p3=as.mid(2,1);
        QString p4=as.mid(3,1);
        QString p5=as.mid(4,1);
        QString p6=as.mid(5,1);
        QString p7=as.mid(6,1);
        QString p8=as.mid(7,1);
        QString p9=as.mid(8,1);
        QString p10=as.mid(9,1);

        //Transformar string
        vcedula[0]=p1.toInt();
        vcedula[1]=p2.toInt();
        vcedula[2]=p3.toInt();
        vcedula[3]=p4.toInt();
        vcedula[4]=p5.toInt();
        vcedula[5]=p6.toInt();
        vcedula[6]=p7.toInt();
        vcedula[7]=p8.toInt();
        vcedula[8]=p9.toInt();
        vcedula[9]=p10.toInt();

        if(vcedula[0]>2)
        {

            est = false;
            break;
        }

        //Pares
        vPar[0]=vcedula[1];
        vPar[1]=vcedula[3];
        vPar[2]=vcedula[5];
        vPar[3]=vcedula[7];
        //Impares
        vImpar[0]=vcedula[0];
        vImpar[1]=vcedula[2];
        vImpar[2]=vcedula[4];
        vImpar[3]=vcedula[6];
        vImpar[4]=vcedula[8];


        //Punto 2. Multiplicacion impar
        for(int i=0; i<5; i++)
        {
            vImpar[i]=vImpar[i]*2;
            if(vImpar[i]>9)
            {
                vImpar[i]=vImpar[i]-9;
            }
            sumaImpar += vImpar[i];
        }
        //Punto 3. Sumar los pares
        for(int i=0; i<4; i++)
        {
            sumaPar += vPar[i];
        }

        total = sumaPar + sumaImpar;

        //Punto 4. Se obtiene el modulo;

        nveri = total%10;


        //Punto 5. Numero verificador
        if(nveri==0)
        {
            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {
                est=false;
                break;
            }
        }else if(nveri !=0)
        {
            nveri=10-nveri;

            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {

                est=false;
                break;
            }
        }

    }while(nu<100000000 || nu>9999999999 || vcedula[0]>2);
    return est;
}

bool Tienda::checkVacios()
{
    bool dato=true;
    //verificar si estan correctos o vacios para pintar el background
    //cedula
    if(verificarCedula(ui->inCedula->text())==false){
        QPalette palette=ui->inCedula->palette();
        palette.setColor(ui->inCedula->backgroundRole(),Qt::red);
        palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
        ui->inCedula->setPalette(palette);
        ui->statusbar->showMessage("Datos erroneos!",3500);
        dato=false;

    }

    else{
        QPalette palette=ui->inCedula->palette();
        palette.setColor(ui->inCedula->backgroundRole(),Qt::green);
        palette.setColor(ui->inCedula->foregroundRole(),Qt::black);
        ui->inCedula->setPalette(palette);
        dato=true;
    }


    if(verificarCedula(ui->inCedula->text())==true){
        if(ui->inCedula->text()=="9999999999"){
            //nombre
            QPalette palette=ui->inNom->palette();
            palette.setColor(ui->inNom->backgroundRole(),Qt::green);
            palette.setColor(ui->inNom->foregroundRole(),Qt::black);
            ui->inNom->setPalette(palette);
            ui->inNom->clear();
            //telefono
            palette=ui->inTelf->palette();
            palette.setColor(ui->inTelf->backgroundRole(),Qt::green);
            palette.setColor(ui->inTelf->foregroundRole(),Qt::black);
            ui->inTelf->setPalette(palette);
            ui->inTelf->clear();
            //email
            palette=ui->inMail->palette();
            palette.setColor(ui->inMail->backgroundRole(),Qt::green);
            palette.setColor(ui->inMail->foregroundRole(),Qt::black);
            ui->inMail->setPalette(palette);
            ui->inMail->clear();
            //direccion
            palette=ui->inDireccion->palette();
            palette.setColor(ui->inDireccion->backgroundRole(),Qt::green);
            palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
            ui->inDireccion->setPalette(palette);
            ui->inDireccion->clear();

            return true;
        }
    }
    //nombre
    if(ui->inNom->text().isEmpty()){
        QPalette palette=ui->inNom->palette();
        palette.setColor(ui->inNom->backgroundRole(),Qt::red);
        palette.setColor(ui->inNom->foregroundRole(),Qt::black);
        ui->inNom->setPalette(palette);
        ui->statusbar->showMessage("Datos erroneos!",3500);
        dato=false;
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
        ui->statusbar->showMessage("Datos erroneos!",3500);
        dato=false;
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
        ui->statusbar->showMessage("Datos erroneos!",3500);
        dato=false;
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
        palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
        ui->inDireccion->setPalette(palette);
        ui->statusbar->showMessage("Datos erroneos!",3500);
        dato=false;
    }
    else{
        QPalette palette=ui->inDireccion->palette();
        palette.setColor(ui->inDireccion->backgroundRole(),Qt::green);
        palette.setColor(ui->inDireccion->foregroundRole(),Qt::black);
        ui->inDireccion->setPalette(palette);
    }
    return dato;
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
    int rows=ui->outDetalle->rowCount();
    while(rows!=-1){
        ui->outDetalle->removeRow(rows);
        rows--;
    }


}

void Tienda::envioString()
{
    int filas=ui->outDetalle->rowCount();
    int contador=0;
    QString detalles="";

    while(contador!=filas){
        detalles+="\t"+ui->outDetalle->item(contador,0)->text()+"\t"+
                ui->outDetalle->item(contador,1)->text()+"\t"+
                ui->outDetalle->item(contador,2)->text()+"\t"+
                ui->outDetalle->item(contador,3)->text()+"\n";
        contador++;
    }
    m_details=detalles;


}

void Tienda::clearOut()
{    ui->outSubtotal_13->setText("0.00");
     ui->outIva->setText("0.00");
      ui->outTotal->setText("0.00");

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
    bool encontrado=false;
    int contador=0;
    if(fila>0){
        while(encontrado==false&&contador!=fila){
            QString nombre=ui->outDetalle->item(contador,1)->text();
            QString comparar=p->nombre();

            if(nombre==comparar){
                QString antiguaCant=(ui->outDetalle->item(contador,0)->text());
                int cant=antiguaCant.toDouble();


                cantidad+=cant;
                subtotal=p->precio()*cantidad;
                ui->outDetalle->setItem(contador,0,new QTableWidgetItem(QString::number(cantidad,'f',2)));
                ui->outDetalle->setItem(contador,3,new QTableWidgetItem(QString::number(subtotal,'f',2)));

                encontrado=true;
            }
            contador++;
        }
    }
    else{}
    if(encontrado==false){
        ui->outDetalle->insertRow(fila);
        ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad,'f',2)));
        ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
        ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(p->precio(),'f',2)));
        ui->outDetalle->setItem(fila,3,new QTableWidgetItem(QString::number(subtotal,'f',2)));

    }
    //limpiar
    ui->inCantidad->setValue(0);
    ui->inNombre->setFocus();

    //calculos
    calcular();

}


void Tienda::on_pushButton_released()
{
    if(checkVacios()==true){
        Finalizacion *finalizar =new Finalizacion(this);
        //agregar variables
        //nombre
        envioString();
        finalizar->setIva(IVA);
        finalizar->setSubtotal(m_subtotal);
        finalizar->insertarDatos(ui->inNom->text(),ui->inCedula->text()
                                 ,ui->inTelf->text(),ui->inMail->text()
                                 ,ui->inDireccion->toPlainText(),m_details);

        finalizar->exec();
        if(finalizar->m_acept==true){
            clearIn();
            clearOut();
        }
        backgroundReset();
    }
}


void Tienda::on_pushButton_2_released()
{
    clearIn();
    clearOut();
    ui->inNom->setFocus();
    backgroundReset();
}


void Tienda::on_actionAcerca_de_TiendaP59_triggered()
{
    AcercaDe *acerca=new AcercaDe(this);
    acerca->exec();
}

