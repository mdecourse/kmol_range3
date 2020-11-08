/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   remove_entity_dialog.cpp                                 *
 *  GROUP:  Range                                                    *
 *  TYPE:   source file (*.cpp)                                      *
 *  DATE:   5-th December 2012                                       *
 *                                                                   *
 *  DESCRIPTION: Remove entity dialog class definition               *
 *********************************************************************/

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

#include "remove_entity_dialog.h"
#include "session.h"
#include "model_action.h"
#include "job_manager.h"

RemoveEntityDialog::RemoveEntityDialog(REntityGroupTypeMask entityTypeMask, QWidget *parent) :
    QDialog(parent),
    entityTypeMask(entityTypeMask)
{
    QIcon closeIcon(":/icons/file/pixmaps/range-close.svg");
    QIcon cancelIcon(":/icons/file/pixmaps/range-cancel.svg");
    QIcon okIcon(":/icons/file/pixmaps/range-ok.svg");

    QString windowTitleStr = tr("Remove entities");
    this->setWindowTitle(tr(windowTitleStr.toUtf8().constData()));

    QGridLayout *mainLayout = new QGridLayout;
    this->setLayout (mainLayout);

    uint nMainLayoutRows = 0;

    QLabel *listLabel = new QLabel(tr("Following entities will be removed:"));
    mainLayout->addWidget(listLabel, ++nMainLayoutRows, 0, 1, 1);

    QList<uint> modelIDs = Session::getInstance().getSelectedModelIDs();

    for (int i=0;i<modelIDs.size();i++)
    {
        QList<SessionEntityID> selectedEntities = this->findEntities(modelIDs[i]);

        QList<SessionEntityID> selectedPoints = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_POINT);
        QList<SessionEntityID> selectedLines = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_LINE);
        QList<SessionEntityID> selectedSurfaces = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_SURFACE);
        QList<SessionEntityID> selectedVolumes = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_VOLUME);
        QList<SessionEntityID> selectedCuts = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_CUT);
        QList<SessionEntityID> selectedIsos = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_ISO);
        QList<SessionEntityID> selectedStreamLines = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_STREAM_LINE);
        QList<SessionEntityID> selectedVectorFields = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_VECTOR_FIELD);
        QList<SessionEntityID> selectedScalarFields = SessionEntityID::filterList(selectedEntities,R_ENTITY_GROUP_SCALAR_FIELD);

        Model &rModel = Session::getInstance().getModel(modelIDs[i]);

        QGroupBox *modelGroupBox= new QGroupBox;
        modelGroupBox->setTitle(rModel.getName());
        mainLayout->addWidget(modelGroupBox, ++nMainLayoutRows, 0, 1, 1);

        QGridLayout *modelGroupLayout = new QGridLayout;
        modelGroupBox->setLayout(modelGroupLayout);

        QString text = "<dl>";
        if (selectedPoints.size())
        {
            text += "<dt>" + tr("Points:");
            text += "<dd>";
            for (int j=0;j<selectedPoints.size();j++)
            {
                text += rModel.getPoint(selectedPoints[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedLines.size())
        {
            text += "<dt>" + tr("Lines:");
            text += "<dd>";
            for (int j=0;j<selectedLines.size();j++)
            {
                text += rModel.getLine(selectedLines[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedSurfaces.size())
        {
            text += "<dt>" + tr("Surfaces:");
            text += "<dd>";
            for (int j=0;j<selectedSurfaces.size();j++)
            {
                text += rModel.getSurface(selectedSurfaces[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedVolumes.size())
        {
            text += "<dt>" + tr("Volumes:");
            text += "<dd>";
            for (int j=0;j<selectedVolumes.size();j++)
            {
                text += rModel.getVolume(selectedVolumes[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedCuts.size())
        {
            text += "<dt>" + tr("Cuts:");
            text += "<dd>";
            for (int j=0;j<selectedCuts.size();j++)
            {
                text += rModel.getCut(selectedCuts[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedIsos.size())
        {
            text += "<dt>" + tr("ISOs:");
            text += "<dd>";
            for (int j=0;j<selectedIsos.size();j++)
            {
                text += rModel.getIso(selectedIsos[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedStreamLines.size())
        {
            text += "<dt>" + tr("Stream lines:");
            text += "<dd>";
            for (int j=0;j<selectedStreamLines.size();j++)
            {
                text += rModel.getStreamLine(selectedStreamLines[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedVectorFields.size())
        {
            text += "<dt>" + tr("Vector fields:");
            text += "<dd>";
            for (int j=0;j<selectedVectorFields.size();j++)
            {
                text += rModel.getVectorField(selectedVectorFields[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        if (selectedScalarFields.size())
        {
            text += "<dt>" + tr("Scalar fields:");
            text += "<dd>";
            for (int j=0;j<selectedScalarFields.size();j++)
            {
                text += rModel.getScalarField(selectedScalarFields[j].getEid()).getName() + QString(",&nbsp;");
            }
        }
        text += "</dl>";

        QLabel *modelLabel = new QLabel(text);
        modelGroupLayout->addWidget(modelLabel,1,0,1,1);
    }

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    mainLayout->addLayout(buttonsLayout, ++nMainLayoutRows, 0, 1, 1);

    QPushButton *cancelButton = new QPushButton(cancelIcon, tr("Cancel"));
    buttonsLayout->addWidget(cancelButton);

    QPushButton *okButton = new QPushButton(okIcon, tr("Ok"));
    okButton->setDefault(true);
    buttonsLayout->addWidget(okButton);

    QObject::connect(cancelButton,&QPushButton::clicked,this,&RemoveEntityDialog::reject);
    QObject::connect(okButton,&QPushButton::clicked,this,&RemoveEntityDialog::accept);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

int RemoveEntityDialog::exec(void)
{
    int retVal = QDialog::exec();

    if (retVal == QDialog::Accepted)
    {
        QList<uint> modelIDs = Session::getInstance().getSelectedModelIDs();
        for (int i=0;i<modelIDs.size();i++)
        {
            ModelActionInput modelActionInput(modelIDs[i]);
            modelActionInput.setRemoveEntities(this->findEntities(modelIDs[i]));

            ModelAction *modelAction = new ModelAction;
            modelAction->setAutoDelete(true);
            modelAction->addAction(modelActionInput);
            JobManager::getInstance().submit(modelAction);
        }
    }

    return retVal;
}

QList<SessionEntityID> RemoveEntityDialog::findEntities(uint mid) const
{
    QList<SessionEntityID> selectedEntities = Session::getInstance().getSelectedEntityIDs();

    for (int i=selectedEntities.size()-1;i>=0;i--)
    {
        if (selectedEntities[i].getMid() == mid
            &&
            selectedEntities[i].getType() & this->entityTypeMask)
        {
            continue;
        }
        selectedEntities.erase(selectedEntities.begin()+i);
    }

    return selectedEntities;
}
