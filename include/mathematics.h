
class region;

#define newRegionPainter(TYPE, CODE) ((region_painter<TYPE>)([](region& region, TYPE * element) CODE))

template <typename T>
using region_painter =  std::function<void(region& reg, T* map)>;

class region {
	private:
		int w;
		int h;
		int x;
		int y;
		
	public:
		
		static const int MIN = -2147483648;
		static const int MAX =  2147483647;
		
		inline static region constructMax() {
			region min(region::MAX, region::MAX, region::MAX, region::MAX);
			return min;	
		}
		
		inline static region constructMin() {
			region max(region::MIN, region::MIN, region::MIN, region::MIN);
			return max;	
		}
		
		region(int px=0, int py=0, int pw=0, int ph=0) {
			x = px;
			y = py;
			w = pw;
			h = ph;
		}
		
		inline int getWidth() {
			return w;
		}
		
		inline int getHeight() {
			return h;
		}
		
		inline int getW() {
			return w;
		}
		
		inline int getH() {
			return h;
		}
		
		inline int getX() {
			return x;
		}
		
		inline int getY() {
			return y;
		}
		
		inline void setWidth(int arg) {
			w = arg;
		}
		
		inline void setHeight(int arg) {
			h = arg;
		}
		
		inline void setW(int arg) {
			w = arg;
		}
		
		inline void setH(int arg) {
			h = arg;
		}
		
		inline void setX(int arg) {
			x = arg;
		}
		
		inline void setY(int arg) {
			y = arg;
		}
		
		template <typename T>
		inline void paint(T*& arr, int W, int H, region_painter<T> rp) {
			for(int iy=y;iy<y+h;++iy) {
				for(int ix=x;ix<x+w;++ix) {
					rp(*this, &arr[ix+iy*W]);
				}
			}
		}

};

