/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   ic_tree.cpp                                              *
 *  GROUP:  Range                                                    *
 *  TYPE:   source file (*.cpp)                                      *
 *  DATE:   6-th August 2012                                         *
 *                                                                   *
 *  DESCRIPTION: Initial condition tree class definition             *
 *********************************************************************/

#include <QStandardItemModel>
#include <QLineEdit>
#include <QPushButton>

#include "component_edit_dialog.h"
#include "session.h"
#include "ic_tree.h"
#include "variable_value_edit.h"
#include "push_button.h"

typedef enum _ICTreeColumn
{
    IC_TREE_PROPERTY_NAME = 0,
    IC_TREE_PROPERTY_VALUE,
    IC_TREE_PROPERTY_UNITS,
    IC_TREE_PROPERTY_TYPE,
    IC_TREE_N_COLUMNS
} ICTreeColumn;

ICTree::ICTree(QWidget *parent) :
    QTreeWidget(parent)
{
    this->setRootIsDecorated(false);
    this->setSelectionMode(QAbstractItemView::NoSelection);

    this->setColumnCount(IC_TREE_N_COLUMNS);

    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(IC_TREE_PROPERTY_TYPE,QString("Property type"));
    headerItem->setText(IC_TREE_PROPERTY_NAME,QString("Property name"));
    headerItem->setText(IC_TREE_PROPERTY_VALUE,QString("Value"));
    headerItem->setText(IC_TREE_PROPERTY_UNITS,QString("Units"));
    this->setHeaderItem(headerItem);

    this->setColumnHidden(IC_TREE_PROPERTY_TYPE,true);

    this->populate();
}

void ICTree::populate(void)
{
    this->clear();

    for (uint i=0;i<this->ic.size();i++)
    {
        RConditionComponent component = this->ic.getComponent(i);

        QTreeWidgetItem *item = new QTreeWidgetItem(this);
        item->setData(IC_TREE_PROPERTY_TYPE,Qt::DisplayRole,QVariant(component.getType()));
        item->setText(IC_TREE_PROPERTY_NAME,component.getName());
        item->setText(IC_TREE_PROPERTY_UNITS,component.getUnits());
        VariableValueEdit *lineEdit = new VariableValueEdit(component.getType());
        lineEdit->setValue(component.getValue(0));
        this->setItemWidget(item,IC_TREE_PROPERTY_VALUE,lineEdit);

        QObject::connect(lineEdit,&VariableValueEdit::valueChanged,this,&ICTree::onIcValueChanged);
    }

    this->resizeColumnToContents(IC_TREE_PROPERTY_NAME);
    this->resizeColumnToContents(IC_TREE_PROPERTY_VALUE);
    this->resizeColumnToContents(IC_TREE_PROPERTY_UNITS);
}

void ICTree::updateSelectedEntities(void) const
{
    QList<SessionEntityID> entityIDs = Session::getInstance().getSelectedEntityIDs();

    for (int i=0;i<entityIDs.size();i++)
    {
        switch (entityIDs[i].getType())
        {
            case R_ENTITY_GROUP_POINT:
                Session::getInstance().getModel(entityIDs[i].getMid()).getPoint(entityIDs[i].getEid()).addInitialCondition(this->ic);
                break;
            case R_ENTITY_GROUP_LINE:
                Session::getInstance().getModel(entityIDs[i].getMid()).getLine(entityIDs[i].getEid()).addInitialCondition(this->ic);
                break;
            case R_ENTITY_GROUP_SURFACE:
                Session::getInstance().getModel(entityIDs[i].getMid()).getSurface(entityIDs[i].getEid()).addInitialCondition(this->ic);
                break;
            case R_ENTITY_GROUP_VOLUME:
                Session::getInstance().getModel(entityIDs[i].getMid()).getVolume(entityIDs[i].getEid()).addInitialCondition(this->ic);
                break;
            default:
                break;
        }
        Session::getInstance().setInitialConditionChanged(entityIDs[i].getMid(),
                                                           entityIDs[i].getType(),
                                                           entityIDs[i].getEid());
    }

    QList<uint> modelIDs = Session::getInstance().getSelectedModelIDs();
    for (int i=0;i<modelIDs.size();i++)
    {
        Session::getInstance().setProblemChanged(modelIDs[i]);
    }
}

void ICTree::onIcSelected(RInitialConditionType icType, bool applied)
{
    if (applied)
    {
        QList<SessionEntityID> entityIDs = Session::getInstance().getSelectedEntityIDs();

        for (int i=0;i<entityIDs.size();i++)
        {
            switch (entityIDs[i].getType())
            {
                case R_ENTITY_GROUP_POINT:
                    this->ic = Session::getInstance().getModel(entityIDs[i].getMid()).getPoint(entityIDs[i].getEid()).getInitialCondition(icType);
                    break;
                case R_ENTITY_GROUP_LINE:
                    this->ic = Session::getInstance().getModel(entityIDs[i].getMid()).getLine(entityIDs[i].getEid()).getInitialCondition(icType);
                    break;
                case R_ENTITY_GROUP_SURFACE:
                    this->ic = Session::getInstance().getModel(entityIDs[i].getMid()).getSurface(entityIDs[i].getEid()).getInitialCondition(icType);
                    break;
                case R_ENTITY_GROUP_VOLUME:
                    this->ic = Session::getInstance().getModel(entityIDs[i].getMid()).getVolume(entityIDs[i].getEid()).getInitialCondition(icType);
                    break;
                default:
                    this->ic.setType(icType);
                    break;
            }
        }

        this->populate();
    }
    else
    {
        this->ic.setType(R_INITIAL_CONDITION_NONE);
        this->clear();
    }
}

void ICTree::onIcValueChanged(RVariableType variableType, double value)
{
    for (uint i=0;i<this->ic.size();i++)
    {
        if (this->ic.getComponent(i).getType() == variableType)
        {
            this->ic.getComponent(i).add(0,value);
        }
    }

    this->updateSelectedEntities();
}
