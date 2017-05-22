#include "aliyun_iot_mqtt_client.h"
#include "aliyun_iot_auth.h"
#include <windows.h>

#define HOST_NAME      "iot-auth.aliyun.com"

//用户需要根据设备信息完善以下宏定义中的四元组内容
#define PRODUCT_KEY    ""
#define PRODUCT_SECRET ""
#define DEVICE_NAME    ""
#define DEVICE_SECRET  ""

//以下三个TOPIC的宏定义不需要用户修改，可以直接使用
//IOT HUB为设备建立三个TOPIC：update用于设备发布消息，error用于设备发布错误，get用于订阅消息
#define TOPIC_UPDATE         "/"PRODUCT_KEY"/"DEVICE_NAME"/update"
#define TOPIC_ERROR          "/"PRODUCT_KEY"/"DEVICE_NAME"/update/error"
#define TOPIC_GET            "/"PRODUCT_KEY"/"DEVICE_NAME"/get"

#define MSG_LEN_MAX 100

/**********************************************************************
 *            接收消息的回调函数
 *
 * 说明：当其它设备的消息到达时，此函数将被执行。
 * 注意：此回调函数中用户在做业务处理时不要使用耗时操作，否则会阻塞接收通道
 **********************************************************************/
static void messageArrived(MessageData *md)
{
    //接收消息缓存
    char msg[MSG_LEN_MAX] = {0};

    MQTTMessage *message = md->message;
    if(message->payloadlen > MSG_LEN_MAX - 1)
    {
        printf("process part of receive message\n");
        message->payloadlen = MSG_LEN_MAX - 1;
    }

    //复制接收消息到本地缓存
    memcpy(msg,message->payload,message->payloadlen);

    //to-do此处可以增加用户自己业务逻辑，例如：开关灯等操作

    //打印接收消息
    printf("Message : %s\n", msg);
}

static void publishComplete(void* context, unsigned int msgId)
{
    printf("publish message is arrived,id = %d\n",msgId);
}

static void subAckTimeout(SUBSCRIBE_INFO_S *subInfo)
{
    printf("msgId = %d,sub ack is timeout\n",subInfo->msgId);
}

int singleThreadDemo(unsigned char *msg_buf,unsigned char *msg_readbuf)
{
	IOT_DEVICEINFO_SHADOW_S deviceInfo;
    int rc = 0;
    char buf[MSG_LEN_MAX] = { 0 };

    //初始化设备参数
    memset(&deviceInfo, 0x0, sizeof(deviceInfo));

    //设备信息初始化
    deviceInfo.productKey = PRODUCT_KEY;
    deviceInfo.productSecret = PRODUCT_SECRET;
    deviceInfo.deviceName = DEVICE_NAME;
    deviceInfo.deviceSecret = DEVICE_SECRET;
    deviceInfo.hostName = HOST_NAME;

    //配置设备信息
    if (0 != aliyun_iot_set_device_info(&deviceInfo))
    {
        printf("run aliyun_iot_set_device_info() error!\n");
        return -1;
    }

    if (0 != aliyun_iot_auth(HMAC_MD5_SIGN_TYPE, IOT_VALUE_FALSE))
    {
        printf("run aliyun_iot_auth() error!\n");
        return -1;
    }

    Client client;
    memset(&client,0x0,sizeof(client));
    IOT_CLIENT_INIT_PARAMS initParams;
    memset(&initParams,0x0,sizeof(initParams));

    initParams.mqttCommandTimeout_ms = 2000;
    initParams.pReadBuf = msg_readbuf;
    initParams.readBufSize = MSG_LEN_MAX;
    initParams.pWriteBuf = msg_buf;
    initParams.writeBufSize = MSG_LEN_MAX;
    initParams.disconnectHandler = NULL;
    initParams.disconnectHandlerData = (void*) &client;
    initParams.deliveryCompleteFun = publishComplete;
    initParams.subAckTimeOutFun = subAckTimeout;
    rc = aliyun_iot_mqtt_init(&client, &initParams);
    if (0 != rc)
    {
        printf("aliyun_iot_mqtt_init failed ret = %d\n", rc);
        return rc;
    }

    MQTTPacket_connectData connectParam;
    memset(&connectParam,0x0,sizeof(connectParam));
    connectParam.cleansession      = 1;
    connectParam.MQTTVersion       = 4;
    connectParam.keepAliveInterval = 180;
    connectParam.willFlag          = 0;

    rc = aliyun_iot_mqtt_connect(&client, &connectParam);
    if (0 != rc)
    {
        aliyun_iot_mqtt_release(&client);
        printf("ali_iot_mqtt_connect failed ret = %d\n", rc);
        return rc;
    }

    rc = aliyun_iot_mqtt_subscribe(&client, TOPIC_GET, QOS1, messageArrived);
    if (0 != rc)
    {
        aliyun_iot_mqtt_release(&client);
        printf("ali_iot_mqtt_subscribe failed ret = %d\n", rc);
        return rc;
    }

    do
    {
        Sleep(200);
        rc = aliyun_iot_mqtt_suback_sync(&client, TOPIC_GET, messageArrived);
    }while(rc != SUCCESS_RETURN);

    MQTTMessage message;
    memset(&message,0x0,sizeof(message));

    //发送字符串消息的内容
    sprintf_s(buf, 50,"{\"message\":\"Hello World\"}");

    message.qos        = QOS1;
    message.retained   = FALSE_IOT;
    message.dup        = FALSE_IOT;
    message.payload    = (void *) buf;   //此处使用的负载是字符串文本数据，如果使用规则引擎请使用JSON格式的字符串
    message.payloadlen = strlen(buf);    //此处使用的负载长度是字符串长度且不包含结束标志'\0',如果负载是二进制数据，则负载长度需要用户准确指定
    message.id         = 0;

    //发送消息
    rc = aliyun_iot_mqtt_publish(&client, TOPIC_UPDATE, &message);
    if (SUCCESS_RETURN != rc)
    {
        aliyun_iot_mqtt_release(&client);
        printf("aliyun_iot_mqtt_publish failed ret = %d\n", rc);
        return rc;
    }

    int ch;
    do
    {
        ch = getchar();
        Sleep(500);
    } while (ch != 'Q' && ch != 'q');

    aliyun_iot_mqtt_release(&client);
	Sleep(200);
    return 0;
}

int main()
{
    printf("start demo!\n");

    unsigned char *msg_buf = (unsigned char *)malloc(MSG_LEN_MAX);
    unsigned char *msg_readbuf = (unsigned char *)malloc(MSG_LEN_MAX);

    //sdk初始化,初始化日志等
    if (0 != aliyun_iot_auth_init())
    {
        printf("run aliyun_iot_auth_init error!\n");
        return -1;
    }

    singleThreadDemo(msg_buf,msg_readbuf);

    free(msg_buf);
    free(msg_readbuf);

    (void) aliyun_iot_auth_release();

    printf("out of demo!\n");

    return 0;
}

