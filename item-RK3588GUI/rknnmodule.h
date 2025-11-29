#ifndef RKNNMODULE_H
#define RKNNMODULE_H

#include "rknn_api.h"
// #include "opencv2/opencv.hpp"

#include <QString>

class RknnModule
{
public:
    // 构造/析构
    RknnModule();
    ~RknnModule();
    // 加载模型
    bool loadModel(QString model_path);
    // 运行模型
    bool runModel();

    // 查询输入输出个数
    // [inputSize, outputSize]
    std::tuple<int, int> checkIOSize();
    // 设置输入
    // void setInput();


private:
    static uint8_t *load_data(FILE *fp, size_t ofst, size_t sz);
    static uint8_t *load_model(QString model_path, int *model_size);

private:
    rknn_context ctx;  //RKNN模型上下文
    uint8_t *model_data;
};

#endif // RKNNMODULE_H
