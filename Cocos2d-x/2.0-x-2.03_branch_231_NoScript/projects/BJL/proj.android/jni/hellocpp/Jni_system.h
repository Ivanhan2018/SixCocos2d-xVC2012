#ifndef JNI_SYSTEM_H
#define JNI_SYSTEM_H


extern "C"
{
	//void gameEnd();
	//void initFinish();
	//void updateServerOnBackground();
	//void setUserScore(const char* str);
	//void setUserEggs(const char* str);
	//void setParking(const char* str);
	//void jniExitView();

	//void openWebview();
	//void liantong_pay(const char* yuan);

	void showRechageLayer(const char* userId,const char* userLevel,const char * dialogID);
	void showFeedBackLayer();
	void checkUpdate();
	void onLineServer();
	void toUserProtion(const char* str);
	void downloadAndriodGame(const char* gameId);
	int getGameExist(int gameID);
	void openGame(const char* gameID);
	void sendOrderID(int _orderID);
	void updateAndriodGame(const char* updateType,const char* packgeSize,const char* downLoadUrl);
	void networkAnomaly();//Õ¯¬Á“Ï≥£
}

#endif // JNI_SYSTEM_H




