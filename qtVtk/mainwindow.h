#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkCameraActor.h>

#include <vtkNamedColors.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkPlanes.h>
#include <vtkMapper.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCylinderSource.h>
#include <vtkSmartPointer.h>
#include <vtkPointCloudFilter.h>
#include <vtkQuad.h>
#include <vtkMath.h>
#include <QMessageBox>
#include <vtkPointSource.h>
#include <vtkFloatArray.h>
#include <vtkPolyData.h>
#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkIntArray.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVertexGlyphFilter.h"
#include "vtkElevationFilter.h"
#include "vtkActor.h"
#include "vtkLookupTable.h"
#include "vtkCoordinate.h"
#include "vtkPointData.h"
#include "vtkDataSetMapper.h"
#include "vtkPolyVertex.h"
#include "vtkUnstructuredGrid.h"
#include "qdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct PointRGB
    {
        double x;
        double y;
        double z;
        double r;
        double g;
        double b;
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Vtk_RGB_Point();


private slots:
    void on_pushButton_gen_clicked();

    void on_pushButton_end_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
