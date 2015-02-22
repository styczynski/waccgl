
class chanim_slide__ : public chanim {
	public:

		inline void init(scene_object* tgt0, scene_object* tgt1) {
			ifaae tgt0->parentX = 0;
			ifaae tgt0->parentY = 0;
			tgt1->parentX = 100;
			tgt1->parentY = 0;
			ifaae tgt0->show(true);
			tgt1->show(true);
		}

		inline void finalize(scene_object* tgt0, scene_object* tgt1) {
			ifaae tgt0->parentX = 0;
			ifaae tgt0->parentY = 0;
			tgt1->parentX = 0;
			tgt1->parentY = 0;

			ifaae tgt0->show(false);
			tgt1->show(true);

			tgt1->flush();

			ANIMATION_IS_PLAYED = false;

			//tgt1->flush();

			//tgt1->flush();
			//tgt0->flush();
			//cout.flush();

		}

		inline int getSteps(scene_object* tgt0, scene_object* tgt1) {
			return 20;
		}

		inline bool nextStep(const int step, scene_object* tgt0, scene_object* tgt1) {
			std::cout<<"nextStep() invoked!\n";std::cout.flush();
			if(tgt1->parentX<10) {
				tgt1->parentX = 10;
				return false;
			}

			ifaae tgt0->parentX -= 15;
			ifaae tgt0->parentY = 0;
			tgt1->parentX -= 15;
			tgt1->parentY = 0;

			//tgt0->flush();
			ifaae tgt0->show(true);
			tgt1->flush();

			std::cout.flush();
			Sleep(100);
			return true;
		}
} chanim_slide;

