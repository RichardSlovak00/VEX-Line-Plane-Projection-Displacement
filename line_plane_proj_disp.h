/* context: Attribute Wrangle (run over points)
 * Creates some interesting displacements on a line plane
 * (or any geometry really), with that being said once you put resample
 * and polyline on this it gets pretty slow  so keep that in mind 
 * */

#define SECOND_INPUT 1
#define SET_COLOR
//#define DEBUG

int prim;
vector uv;

float maxBBox_1 = getbbox_max(geoself()).y;
float maxBBox_2 = getbbox_max(SECOND_INPUT).z;
float dist = xyzdist(SECOND_INPUT,@P,prim,uv,maxBBox_2);

vector prim_pos = primuv(SECOND_INPUT,"P",prim,uv);
vector prim_norm = primuv(SECOND_INPUT,"N",prim,uv);
vector prim_Cd = primuv(SECOND_INPUT,"Cd",prim,uv);

// parameters
/* outside is used for displacements outside of the area where it gets mapped
 * potentialy can get inversed and have the opposite effect
 * */
float outside_max_dist = chf("outside_max_dist");
float outside_min_dist = chf("outside_min_dist");
float outside_dist_blend = fit(dist, outside_min_dist, outside_max_dist, 0, 1);
float noise_freq = chf("freq");
float displacement_amp = chf("displacement_amp");

vector noise_amp = chv("amp");

/* used to determine whether we should map the plane
 * onto the primitive position of the given object
 * */
float tol = chf("tol");

// curl noise gives better results but can try both
vector curl_noise_pos = ((curlnoise(@P * noise_freq) - set(0.5, 0.5, 0.5) ) * noise_amp ) * outside_dist_blend;

//vector perlin_noise_pos = ((noise(@P * noise_freq) - set(0.5, 0.5, 0.5)) * noise_amp ) * dist_blend;

@P += curl_noise_pos;
vector dir = @P - prim_pos;

// use the dot product to determine whether we are inside the object (given the tolerance)
float product = dot(dir,prim_norm);

#ifdef DEBUG
f@product = product;
#endif /* DEBUG */

if(product < tol){
        /* used for inside displacements, that is for the parts where the object is located */
        float inside_max_dist = chf("inside_max_dist");
        float inside_min_dist = chf("inside_min_dist");
        float inside_dist_blend = fit(dist, inside_min_dist, inside_max_dist, 0, 1);

        @P = lerp(@P,prim_pos,inside_dist_blend * displacement_amp);
        
        /* we use the color from the objects
         * (when the objects are not distorted too much this clearly projects
         * the object onto the plane, which gives a quite nice effect as well
         * and can transition pretty nicely into the distorted stuff)
         * */
        #ifdef SET_COLOR
        v@Cd = prim_Cd;
        #endif /* SET_COLOR */
    
}

