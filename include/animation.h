
#include <pthread.h>
#define ifaae if(two_arg)

bool ANIMATION_IS_PLAYED = false;

inline bool isAnimationPlayed() {
	return ANIMATION_IS_PLAYED;
}

class animation {

	private:
		static void* animation_thread(void *arg) {
			for(int it=0;it<100;++it) {
				if( !((animation*)arg)->nextStep(it) ) {
					return nullptr;
				}
			}
			return nullptr;
		}
		
	public:
		inline virtual bool nextStep(const int step) {
			return true;
		}
		
		inline void run() {
			ANIMATION_IS_PLAYED = true;
			pthread_t t1;
    		pthread_create(&t1, NULL, animation_thread, (void*)this);
		}	
};





class chanim {

	private:
		static void* chanimation_thread(void *arg) {
			if(((chanim*)arg)->two_arg) {
				for(int it=0;it<((chanim*)arg)->getSteps(((chanim*)arg)->tgt0,((chanim*)arg)->tgt1);++it) {
					if( !(((chanim*)arg)->nextStep(it,((chanim*)arg)->tgt0,((chanim*)arg)->tgt1)) ) {
						break;
					}
				}
				((chanim*)arg)->finalize(((chanim*)arg)->tgt0, ((chanim*)arg)->tgt1);
			} else {
				for(int it=0;it<((chanim*)arg)->getSteps(nullptr,((chanim*)arg)->tgt1);++it) {
					if( !(((chanim*)arg)->nextStep(it,nullptr,((chanim*)arg)->tgt1)) ) {
						break;
					}
				}
				((chanim*)arg)->finalize(nullptr,((chanim*)arg)->tgt1);
			}
			return nullptr;
		}
		
	public:
		scene_object* tgt0;
		scene_object* tgt1;
		bool two_arg;
		
		inline virtual bool nextStep(const int step, scene_object* tgt0, scene_object* tgt1) {
			return true;
		}
		
		inline virtual void init(scene_object* tgt0, scene_object* tgt1) {
			
		}
		
		inline virtual void finalize(scene_object* tgt0, scene_object* tgt1) {
			ANIMATION_IS_PLAYED = false;
		}
		
		inline virtual int getSteps(scene_object* tgt0, scene_object* tgt1) {
			return 100;
		}
		
		inline void run(scene_object* arg0, scene_object* arg1) {
			std::cout<<"run(a,b) invoked!\n";std::cout.flush();
			two_arg = true;
			tgt0 = arg0;
			tgt1 = arg1;
			pthread_t t1;
			std::cout<<"init(a,b) invoked!\n";std::cout.flush();
			init(tgt0, tgt1);
			
			if(getSteps(tgt0,tgt1)<0) {
				std::cout<<"finalize(a,b) invoked!\n";std::cout.flush();
				finalize(tgt0,tgt1);
				std::cout<<"end invoked!\n";std::cout.flush();
				return;
			}
    		pthread_create(&t1, NULL, chanimation_thread, (void*)this);
		}	
		
		inline void run(scene_object* arg0) {
			two_arg = false;
			tgt1 = arg0;
			pthread_t t1;
			init(nullptr,tgt1);
			if(getSteps(nullptr,tgt1)<0) {
				finalize(nullptr,tgt1);
				return;
			}
    		pthread_create(&t1, NULL, chanimation_thread, (void*)this);
		}	
};

