#include "rknnmodule.h"

#include <QMessageBox>



RknnModule::RknnModule()
{

}

RknnModule::~RknnModule()
{
    rknn_destroy(ctx);
    delete model_data;
}

bool RknnModule::loadModel(QString model_path)
{
    printf("Loading mode...\n");
    int model_data_size = 0;
    model_data = load_model(model_path, &model_data_size);
    int ret = rknn_init(&ctx, model_data, model_data_size, 0);
    if (ret < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("rknn_init error ret="+QString::number(ret));
        msgBox.exec();
        return false;
    }
    return true;
}

bool RknnModule::runModel()
{
    int ret =rknn_run(ctx, NULL);
    if (ret < 0)
    {
        return false;
    }
    return true;
}

std::tuple<int, int> RknnModule::checkIOSize()
{
    rknn_input_output_num io_num;
    int ret = rknn_query(ctx, RKNN_QUERY_IN_OUT_NUM, &io_num, sizeof(io_num));
    if (ret < 0)
        return std::make_tuple(0,0);
    else
        return std::make_tuple(io_num.n_input, io_num.n_output);
}

uint8_t *RknnModule::load_data(FILE *fp, size_t ofst, size_t sz)
{
    uint8_t *data;
    int ret;
    data = NULL;
    if (NULL == fp)
    {
        return NULL;
    }
    ret = fseek(fp, ofst, SEEK_SET);
    if (ret != 0)
    {
        QMessageBox msgBox;
        msgBox.setText("blob seek failure.");
        msgBox.exec();
        return NULL;
    }
    data = (unsigned char *)malloc(sz);
    if (data == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("buffer malloc failure.");
        msgBox.exec();
        return NULL;
    }
    fread(data, 1, sz, fp);
    return data;
}

uint8_t *RknnModule::load_model(QString model_path, int *model_size)
{
    FILE *fp;
    unsigned char *data;
    fp = fopen(model_path.toLocal8Bit(), "rb");
    if (NULL == fp)
    {
        QMessageBox msgBox;
        msgBox.setText(model_path+"模型文件打开失败！");
        msgBox.exec();
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    data = load_data(fp, 0, size);
    fclose(fp);
    *model_size = size;
    return data;
}
