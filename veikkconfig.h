/**
 * This MainWindow class adds functionality to the basic UI in Ui::MainWindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QScreen>
#include <QCheckBox>
#include <QComboBox>

// supported modparm types -- may not line up with
// enum veikk_modparms from the driver
typedef enum {
    VEIKK_MP_SCREEN_MAP		= 0x1,
    VEIKK_MP_SCREEN_SIZE 	= 0x2,
    VEIKK_MP_ORIENTATION 	= 0x4,
    VEIKK_MP_PRESSURE_MAP 	= 0x8,
    VEIKK_MP_SCREEN			= 0x7,
    VEIKK_MP_ALL			= 0xf
} ModparmType;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QScreen *screen;

    // relevant elements
    QTabWidget *tabWidget;
    QGraphicsView *pressureCurveView, *screenMapView;

    // control elements
    QDoubleSpinBox *pressureCoefSpinboxes[4];
    QSpinBox *screenMapXSpinBox, *screenMapYSpinBox,
             *screenMapWidthSpinBox, *screenMapHeightSpinBox,
             *screenMapSpinboxes[4];
    QLineEdit *screenWidthLineEdit, *screenHeightLineEdit;
    QCheckBox *screenDefaultMap;
    QComboBox *screenOrientation;

    // handlers
    void showEvent(QShowEvent *evt) override;
    void resizeEvent(QResizeEvent *evt) override;

    // composite parameter value getters
    void getPressureCoefs(qint16 *coefs);
    QRect getScreenMapParms();
    QString getExportFormat(ModparmType type);

    // module parameter functions
    int setSysfsModparm(QString parmName, QString value);

public slots:
    void screenSizeChanged(QRect newScreenSize);
    void tabChanged(int curTab);
    void updatePressureForm(qint16 *newCoefs);
    void updatePressureCoefs();
    void updateScreenMapForm(QRect newScreenMap);
    void updateScreenMapParms();
    void setDefaultScreenMap(int checkState);

    void exportConfig(ModparmType type);
    void exportConfigToFile(QString &dest);
signals:
    void updatePressureCurve(qint16 *newCoefs);
    void updateScreenMapRect(QRect newScreenMap);
};
#endif // MAINWINDOW_H
