#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
//#include <condition_variable>
#include <unistd.h>
 
class CThreadMsg
{
private:
	std::deque<int> m_data;
	std::mutex m_mtx; // 全局互斥锁.
	//std::condition_variable m_cv; // 全局条件变量.
	int       m_nGen;
 
public:
 
	void send_all()
	{
		//m_cv.notify_all();
	}
	
	void send(){
			//std::unique_lock <std::mutex> lck(m_mtx);
			std::lock_guard <std::mutex> lck(m_mtx);
			m_nGen = ++m_nGen % 1000;
			printf("product %d\n", m_nGen);
			m_data.push_back(m_nGen);
			//lck.unlock();
			//m_cv.notify_one();
	}
 
	void ConsumerRecv(){
		while (true){
			sleep(2);
			//std::unique_lock <std::mutex> lck(m_mtx);
			std::lock_guard <std::mutex> lck(m_mtx);
/* 			while (m_data.empty()){
				m_cv.wait(lck);
			} */
			int nData = m_data.front();
			m_data.pop_front();
			printf("consume %d\n", nData);
			//lck.unlock();
		}
	}
	
	CThreadMsg(){
		m_data.clear();
		m_nGen = 0;
	}
 
	virtual ~CThreadMsg()
	{
		send_all();
		
	}
 
	void Start(){
		std::thread t(&CThreadMsg::ConsumerRecv, this);
		t.detach();
		
	}
};
 
 
int main()
{
	CThreadMsg test;
	test.Start();
	int i = 10;
	while(1)
	{
		i--;
		if(i> 0)
		    test.send();
		sleep(1);
	}
	return 0;
}