#include "NNLayerParams.h"

#include <sstream>

#include "ActivationFunc.h"
#include "InitializerFunc.h"
#include "Normalization.h"
#include "Dropout.h"
#include "Recurrent.h"

#include "LinearLayerParams.h"
#include "Conv1dLayerParams.h"
#include "Conv2dLayerParams.h"
#include "PoolLayerParams.h"
#include "EmbeddingLayerParams.h"
#include "ReshapeLayerParams.h"
#include "NormalizationLayerParams.h"
#include "ActivationLayerParams.h"
#include "ConcatinateLayerParams.h"
#include "Pool2dLayerParams.h"
#include "DropoutLayerParams.h"
#include "FlattenLayerParams.h"
#include "RecurrentLayerParams.h"

NNLayerParams::NNLayerParams(const std::string& strName, const std::vector<NNParam>& vParams)
    : m_strName{strName},
      m_vParams{vParams}
{

}

std::shared_ptr<NNLayerParams> NNLayerParams::makeLinear()
{
    auto strName = "Linear";

    std::vector<NNParam> vParams = {NNParam{"input_size", 0},
                                    NNParam{"output_size", 0},
                                    NNParam{InitializerFunc::getClassName(),
                                            InitializerFunc{static_cast<initializer_func>(0)}.toString(),
                                            QVariant::Type::String, true}};

    return std::make_shared<LinearLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeConv1d()
{
    auto strName = "Conv1d";
    std::vector<NNParam> vParams = {NNParam{"in_depth", 0},
                                    NNParam{"out_depth", 0},
                                    NNParam{"kernel_size", 0},
                                    NNParam{"stride", 1},
                                    NNParam{"padding", 0},
                                    NNParam{"dilitation", 1},
                                    NNParam{InitializerFunc::getClassName(),
                                            InitializerFunc{static_cast<initializer_func>(0)}.toString(),
                                            QVariant::Type::String, true}};

    return std::make_shared<Conv1dLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeConv2d()
{
    auto strName = "Conv2d";
    std::vector<NNParam> vParams = {NNParam{"in_depth", 0},
                                    NNParam{"out_depth", 0},
                                    NNParam{"kernel_size", QList<QVariant>{0, 0}, QVariant::Type::List},
                                    NNParam{"stride", QList<QVariant>{1, 1}, QVariant::Type::List},
                                    NNParam{"padding", QList<QVariant>{0, 0}, QVariant::Type::List},
                                    NNParam{"dilitation", QList<QVariant>{1, 1}, QVariant::Type::List},
                                    NNParam{InitializerFunc::getClassName(),
                                            InitializerFunc{static_cast<initializer_func>(0)}.toString(),
                                            QVariant::Type::String, true}};

    return std::make_shared<Conv2dLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makePool()
{
    auto strName = "Pool";
    std::vector<NNParam> vParams = {NNParam{"kernel_size", 0}, NNParam{"stride", 1}, NNParam{"padding", 0}, NNParam{"dilitation", 1}};

    return std::make_shared<PoolLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makePool2d()
{
    auto strName = "Pool2d";
    std::vector<NNParam> vParams = {NNParam{"kernel_size", QList<QVariant>{0, 0}, QVariant::Type::List},
                                    NNParam{"stride", QList<QVariant>{1, 1}, QVariant::Type::List},
                                    NNParam{"padding", QList<QVariant>{0, 0}, QVariant::Type::List},
                                    NNParam{"dilitation", QList<QVariant>{1, 1}, QVariant::Type::List},
                                    NNParam{InitializerFunc::getClassName(),
                                            InitializerFunc{static_cast<initializer_func>(0)}.toString(),
                                            QVariant::Type::String, true}};

    return std::make_shared<Pool2dLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeEmbedding()
{
    auto strName = "Embedding";
    std::vector<NNParam> vParams = {NNParam{"vocab_size", 0}, NNParam{"embedding_size", 0}};

    return std::make_shared<EmbeddingLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeReshape()
{
    auto strName = "Reshape";
    std::vector<NNParam> vParams = {NNParam{"size", QList<QVariant>{}, QVariant::Type::List}}; ///< @todo

    return std::make_shared<ReshapeLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeNormalization()
{
    auto strName = "Normalization";
    std::vector<NNParam> vParams = {NNParam{Normalization::getClassName(),
                                            Normalization{enu_normalization::batchnorm1d}.toString(),
                                            QVariant::Type::String, true},
                                    NNParam{"strange_param", 0}};

    return std::make_shared<NormalizationLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeActivation()
{
    auto strName = ActivationFunc::getClassName();

    std::vector<NNParam> vParams = {NNParam{ActivationFunc::getClassName(),
                                            ActivationFunc{activation_func::relu}.toString(),
                                            QVariant::Type::String, true}};

    return std::make_shared<ActivationLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeConcatinate()
{
    auto strName = "Concatinate";
    std::vector<NNParam> vParams = {NNParam{"axis", 0}};

    return std::make_shared<ConcatinateLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeDropout()
{
    auto strName = "Dropout";
    std::vector<NNParam> vParams = {NNParam{Dropout::getClassName(),
                                            Dropout{enu_dropout::dropout}.toString(),
                                            QVariant::Type::String, true},
                                    NNParam{"p", 0, QVariant::Type::Double}};

    return std::make_shared<DropoutLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeFlatten()
{
    auto strName = "Flatten";
    std::vector<NNParam> vParams = {NNParam{"axis_to_flat", QList<QVariant>{0, 1}, QVariant::Type::List}};

    return std::make_shared<FlattenLayerParams>(strName, vParams);
}

std::shared_ptr<NNLayerParams> NNLayerParams::makeRecurrent()
{
    auto strName = "Recurrent";
    std::vector<NNParam> vParams = {NNParam{Recurrent::getClassName(),
                                            Recurrent{enu_recurrent::gru}.toString(),
                                            QVariant::Type::String, true},
                                    NNParam{"input_size", 0},
                                    NNParam{"hidden_size", 0},
                                    NNParam{"num_layers", 0},
                                    NNParam{"bias", false, QVariant::Type::Bool},
                                    NNParam{"bidirectional", false, QVariant::Type::Bool}};

    return std::make_shared<RecurrentLayerParams>(strName, vParams);
}

void NNLayerParams::setName(const std::string& strName) noexcept
{
    m_strName = strName;
}

const std::string& NNLayerParams::getName() const noexcept
{
    return m_strName;
}

const std::vector<NNParam>& NNLayerParams::getParams() const noexcept
{
    return m_vParams;
}

void NNLayerParams::setParams(const std::vector<NNParam>& vParams) noexcept
{
    m_vParams = vParams;
}

bool NNLayerParams::isValid() const noexcept
{
    return !m_vParams.empty();
}

QString NNLayerParams::getDisplayName() const noexcept
{
    return QString::fromStdString(m_strName);
}

std::string NNLayerParams::makeXmlString() const
{
    std::stringstream Stream;

    Stream << "<type>" << m_strName << "</type>" << std::endl;

    for (const auto& spParams : m_vParams)
        Stream << spParams.makeXmlString();

    return Stream.str();
}
