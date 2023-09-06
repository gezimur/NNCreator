#include "ParamsEditorWidget.h"

#include <QHBoxLayout>
#include "ParamWidget.h"

ParamsEditorWidget::ParamsEditorWidget()
    : m_pNameLabel{new QLabel},
      m_pParamsLayout{new QVBoxLayout},
      m_pConfirm{new QPushButton{"Confirm"}},
      m_pDelete{new QPushButton{"Delete"}}
{
    initGUI();
    createConnections();
}

void ParamsEditorWidget::onSetParams(const NNLayerParams& crParams)
{
    m_Params = crParams;
    initEditors();
    update();
}

void ParamsEditorWidget::onConfirmParams()
{
    if (!m_Params.isValid())
        return ;

    m_Params = collectParams();

    emit paramsChanged(m_Params);
}

void ParamsEditorWidget::initGUI()
{
    auto pButtonsLayout = new QHBoxLayout;

    pButtonsLayout->addWidget(m_pConfirm);
    pButtonsLayout->addWidget(m_pDelete);

    auto pMainLayout = new QVBoxLayout{this};

    pMainLayout->addWidget(m_pNameLabel);
    pMainLayout->addLayout(m_pParamsLayout);
    pMainLayout->addLayout(pButtonsLayout);
    pMainLayout->addSpacerItem(new QSpacerItem{10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding});
}

void ParamsEditorWidget::createConnections()
{
    auto bRes = true;

    bRes &= static_cast<bool>(connect(m_pConfirm, SIGNAL(clicked(bool)), SLOT(onConfirmParams())));
    bRes &= static_cast<bool>(connect(m_pDelete, SIGNAL(clicked(bool)), SIGNAL(deleteActive())));

    assert(bRes);
}

void ParamsEditorWidget::initEditors()
{
    while (auto pItem = m_pParamsLayout->itemAt(0))
    {
        auto pWdg = pItem->widget();
        if (!pWdg)
            continue;

        pWdg->close();
        m_pParamsLayout->removeWidget(pWdg);
    }

    m_pNameLabel->setText(QString::fromStdString(m_Params.getName()));

    for(const auto& crParam : m_Params.getParams())
    {
        m_pParamsLayout->addWidget(new ParamWidget{crParam});
    }
}

const NNLayerParams& ParamsEditorWidget::collectParams()
{
    std::vector<NNParam> vParams;

    for (auto i = 0; i < m_pParamsLayout->count(); ++i)
    {
        auto pWdg = static_cast<ParamWidget*>(m_pParamsLayout->itemAt(i)->widget());
        if (pWdg)
            vParams.push_back(pWdg->collectValue());
    }

    m_Params.setParams(vParams);
    return m_Params;
}
