// Thread safe ringbuffer implementation
// Credits : EmbeddedArtistry.com

#include <iostream>
#include <memory>
#include <mutex>

template <class T>
class circular_buffer {
  public:
 
    explicit circular_buffer(size_t size) :
            buf_(std::unique_ptr<T[]>(new T[size])), max_size_(size){}

    // API
       void put(T item);
       T get();
       void reset();
       bool isEmpty();
       bool isFull();
      
       size_t capacity() const;
       size_t size() const;

       void show();


  private:
    std::mutex mutex_;
 
    std::unique_ptr<T[]> buf_;
    const size_t max_size_;

    size_t head_ = 0;
    size_t tail_ = 0;
  
    bool full_ = 0;
    
};

template<typename T>
void circular_buffer<T> :: reset()
{
   std::lock_guard<std::mutex> lock(mutex_);
   head_ = tail_;
   full_ = false;
}

template<typename T>
bool circular_buffer<T> :: isEmpty()
{
   return (!full_ && (head_ == tail_));
}

template<typename T>
bool circular_buffer<T> :: isFull() 
{
   return full_;
}
template<typename T>
void circular_buffer<T> :: put(T item)
{
   std::lock_guard<std::mutex> lock(mutex_);

   buf_[head_] = item;

   if (full_) 
   {
      tail_ = (tail_ +1) % max_size_;
   }

   head_ = (head_ + 1) % max_size_;

   full_ = (head_== tail_);

#if DEBUG 
   std::cout << "put() :: Head : " << head_ << " " << "Tail : " << tail_ << std::endl;
#endif  

   return;       
}

template<typename T>
T circular_buffer<T> :: get()
{
  std::lock_guard<std::mutex> lock(mutex_);

  if (isEmpty()) 
  {
     return T();
  }

  auto val =  buf_[tail_];

  full_ = false;

  tail_ = (tail_ + 1) % max_size_;

#if DEBUG
  std::cout << "get() :: Head : " << head_ << " " << "Tail : " << tail_ << std::endl;
#endif

  return val; 
 
}

template<typename T>
size_t circular_buffer<T> :: capacity() const
{
   return max_size_;
} 

template<typename T>
size_t circular_buffer<T> :: size() const
{

 size_t size = max_size_;

    if(!full_)
    {
        if(head_ >= tail_)
        {
            size = head_ - tail_;
        }
        else
        {
            size = max_size_ + head_ - tail_;
        }
    }

   return size;
}

template<typename T>
void circular_buffer<T> :: show()
{
   if (head_ > tail_)
   {
      for(int i= tail_; i < head_; i++)
      std::cout << buf_[i] << " ";
   }
   else
   {
      for(int i=0; i < head_; i++)
      {
         std::cout << buf_[i] << " ";
      }
      for (int i= tail_; i < max_size_; i++)
      {
         std::cout << buf_[i] << " ";
      }
   }

   std::cout << std::endl;
}

int main()
{
   circular_buffer<int> cbuf(5);

   cbuf.put(10);
   cbuf.put(20);
   cbuf.put(30); 
   cbuf.put(40); 
   cbuf.put(50);

   cbuf.show();

   cbuf.put(60);
   cbuf.show();
   
   cbuf.get();
   cbuf.show();

   cbuf.put(25);
   cbuf.show();

   cbuf.put(35);
   cbuf.show();

   cbuf.get();
   cbuf.show();

   return 0;
}
