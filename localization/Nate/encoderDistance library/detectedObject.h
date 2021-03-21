#ifndef DETECTEDOBJECT_H
#define DETECTEDOBJECT_H


class detectedObject {
    public:
         
        unsigned long distanceFromBot;
        long xAxis, yAxis, angle; 
        unsigned long convert();

    private:
        detectedObject();
        detectedObject(long);
        void update(); 
        

}; 

#endif