#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include<iostream>
#include<time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString button_style="QPushButton{background-color:black;\
    color: white;   border-radius: 10px;  border: 2px groove gray;\
    border-style: outset;}"
    "QPushButton:hover{background-color:white; color: black;}"
    "QPushButton:pressed{background-color:rgb(85, 170, 255);\
    border-style: inset; }";

    //ui->label_point_num->setStyleSheet("background-color:gray");
    //ui->label_point_size->setStyleSheet("background-color:gray");
    ui->lineEdit_point_num ->setStyleSheet("border-radius: 10px;  border: 2px groove gray");
    ui->lineEdit_line_size ->setStyleSheet("border-radius: 10px;  border: 2px groove gray");
    ui->lineEdit_R->setStyleSheet("border-radius: 10px;  border: 2px groove gray");
    ui->lineEdit_G->setStyleSheet("border-radius: 10px;  border: 2px groove gray");
    ui->lineEdit_B->setStyleSheet("border-radius: 10px;  border: 2px groove gray");
    ui->label_runTime_display->setStyleSheet("border-radius: 10px;  border: 2px groove gray");
    ui->pushButton_gen->setStyleSheet(button_style);
    ui->pushButton_end->setStyleSheet(button_style);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Vtk_RGB_Point()
{
    clock_t start,finish;
    double totaltime;
    start=clock();
    ui->qvtkWidget->setSizeIncrement(ui->centralWidget->sizeIncrement().height(),ui->centralWidget->sizeIncrement().width());
    vtkSmartPointer<vtkRenderer> Renderer = vtkSmartPointer<vtkRenderer>::New();
    std::vector<MainWindow::PointRGB> pointrgb;
    vtkSmartPointer<vtkActor> anActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPolyVertex> polyVertex = vtkSmartPointer<vtkPolyVertex>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    vtkSmartPointer<vtkFloatArray>pointsScalars = vtkSmartPointer<vtkFloatArray>::New();
    vtkSmartPointer<vtkUnstructuredGrid> aGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkDataSetMapper> aMapper = vtkSmartPointer<vtkDataSetMapper>::New();

    double x = 0, y = 0, z = 0;
    double r = 0, g = 0, b = 0;
    std::string str = ui->lineEdit_point_num->text().toStdString();
    int n = atoi(str.c_str());
    for(int i =0;i<n;i++)
    {
        MainWindow::PointRGB point;
        x = vtkMath::Random(0.0,5.0);
        y = vtkMath::Random(0.0,5.0);
        z = vtkMath::Random(0.0,5.0);
        r = vtkMath::Random(0.0,255.0);
        g = vtkMath::Random(0.0,255.0);
        b = vtkMath::Random(0.0,255.0);
        point.x = x; point.y = y; point.z = z;
        point.r = r; point.g = g; point.b = b;
        pointrgb.push_back(point);
    }
    //根据点云坐标以及颜色信息，构造vtk中的actor
    //参数：点云读取出来的xyz坐标信息 点云读取出来的RGB信息 vtk中的actor
    size_t number = pointrgb.size(); //几何数据
    points->SetNumberOfPoints(number);
    lut->SetNumberOfTableValues(number);
    lut->Build();

    for (int i = 0; i < number; i++)
    {
        points->InsertPoint(i, pointrgb[i].x, pointrgb[i].y, pointrgb[i].z);
        lut->SetTableValue(i, pointrgb[i].r / 255.0, pointrgb[i].g / 255.0, pointrgb[i].b / 255.0, 1);
    } //拓扑数据

    polyVertex->GetPointIds()->SetNumberOfIds(number);//polyVertex,用于多点绘制，必须设置Id个数，否则可以编译，不能运行

//    pointsScalars->SetNumberOfTuples(number);//此行可有可无
    for (int i = 0; i < number; i++)
    {
        polyVertex->GetPointIds()->SetId(i, i);//第一个参数是几何point的ID号，第2个参数是拓扑中的Id号
        pointsScalars->InsertValue(i,i);//第1个参数是points点的Id，第2个参数是该点的属性值
    }
    aGrid->Allocate(1, 1);
    aGrid->SetPoints(points);
    aGrid->GetPointData()->SetScalars(pointsScalars);
    aGrid->InsertNextCell(polyVertex->GetCellType(), polyVertex->GetPointIds()); //设置映射器

    aMapper->SetInputData(aGrid);
    aMapper->ScalarVisibilityOn();
    aMapper->SetScalarRange(0, number - 1);
    aMapper->SetLookupTable(lut);

    anActor->SetMapper(aMapper);
    anActor->GetProperty()->SetRepresentationToPoints(); //anActor->GetProperty()->SetDiffuseColor(1,0,0);
    std::string sizeStr = ui->lineEdit_line_size->text().toStdString();
    int pointsize =atoi(sizeStr.c_str());
    anActor->GetProperty()->SetPointSize(pointsize);
    std::string colorR = ui->lineEdit_R->text().toStdString();
    int R =atoi(colorR.c_str());
    std::string colorG = ui->lineEdit_G->text().toStdString();
    int G =atoi(colorG.c_str());
    std::string colorB = ui->lineEdit_B->text().toStdString();
    int B =atoi(colorB.c_str());
    Renderer->SetBackground(R,G,B);

    //leftRenderer->AddActor(sphereActor);
    //newRenderer->SetBackground(255, 255, 255);
    Renderer->AddActor(anActor);
//    Renderer->ResetCamera();
//    Renderer->DrawOn();
//    ui->qvtkWidget->GetRenderWindow()->Render();
    vtkRenderWindow *renderWindow = vtkRenderWindow::New();
    renderWindow->AddRenderer(Renderer);
    ui->qvtkWidget->SetRenderWindow(renderWindow);
//    ui->qvtkWidget->GetRenderWindow()->AddRenderer(Renderer);
    ui->qvtkWidget->update();

    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;

    std::string run_time = std::to_string(totaltime)+"sec";
    QString qstring = QString(QString::fromLocal8Bit(run_time.c_str()));
    ui->label_runTime_display->setText(qstring);

}

void MainWindow::on_pushButton_gen_clicked()
{
    Vtk_RGB_Point();
}

void MainWindow::on_pushButton_end_clicked()
{
    QApplication::exit();
}







