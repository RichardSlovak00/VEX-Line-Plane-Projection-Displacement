/* context: Attribute Wrangle (run over detail(only once)) 
 * Creates a plane made of lines seperated by distance of step_size
 * */

// parameters
int num_lines = chi("num_lines");
float step_size = chf("step_size");
vector initialPos = chv("initial_position");
float height = chf("height");

setdetailattrib(0,"height",height);

for (int i = 0; i < num_lines; i++) {
        int pt1 = addpoint(0,initialPos);
        vector pos2 = initialPos;
        pos2.y += height;
        int pt2 = addpoint(0,pos2);
        int line = addprim(0,"polyline",pt1,pt2);
        initialPos.x = step_size * i/num_lines;
}

