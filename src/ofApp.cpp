#include "ofApp.h"

short MAP_WIDTH;                
short MAP_HEIGHT;
float viscosity;
short numThreads;
int particlesPerThread;
short total_particles = -1;
short number_of_particles[NUM_TYPES] = {200,200,200};                       // per type (color)
float force_matrix[NUM_TYPES][NUM_TYPES]{{0}};               // the forces of attraction of each individual color against every other color
int color_force_range_matrix_squared[NUM_TYPES][NUM_TYPES]{{0}};      // the force range of each individual color againts every other color
                                                                        // squared so we save computational time on compute force and 
                                                                        // dont calculate the square distance thouasands of times needlesly


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0,0,0);    // Black Background Color
    // The map is offset MAP_BORDER in both axis for better visibility
    MAP_WIDTH = 0.75 * ofGetScreenWidth() + MAP_BORDER;      
    MAP_HEIGHT = 0.95 * ofGetScreenHeight() + MAP_BORDER;
    
    numThreads = std::thread::hardware_concurrency(); // Get the number of available hardware threads
    if (numThreads == 0) {
        numThreads = 1; // Fallback to 1 if hardware_concurrency() is not well-defined
        ofLogError() << "Only 1 thread is being utilized"; 
    }
    initialize_forces(-MAX_FORCE,MAX_FORCE);
    create_settings_dir();
    
    //========================= CREATE GUI =========================================
    gui.setup("Settings");
    gui.setPosition(MAP_WIDTH+70,20);
    gui.setWidthElements(260);
    gui.add(button_restart.setup("RESTART (R)"));
    button_restart.addListener(this,&ofApp::restart);
    gui.add(button_shuffle.setup("SHUFFLE (S)"));
    button_shuffle.addListener(this,&ofApp::shuffle);
    gui.add(toggle_shuffle_numbers.setup("Shuffle Number of Particles",false));
    gui.add(toggle_shuffle_radi.setup("Shuffle Radius",false));

    SimSettings.setup("Simulation Settings");
    gui.add(&SimSettings);
    SimSettings.add(slider_viscosity.setup("VISCOSITY",0.001F,0.0F,0.1F));  //Max Viscosity 0.1
    SimSettings.add(slider_wall_repel_force.setup("WALL REPEL FORCE",0.1F,0,WALL_REPEL_FORCE_MAX));

    RedSettings.setup("RED SETTINGS");
    SimSettings.add(&RedSettings);
    RedSettings.add(field_number_R.setup("Number of Particles",number_of_particles[RED],1,MAX_PARTICLES));
    RedSettings.add(sliderRR.setup("RED X RED",force_matrix[RED][RED],-MAX_FORCE,MAX_FORCE));
    RedSettings.add(sliderRG.setup("RED X GREEN",force_matrix[RED][GREEN],-MAX_FORCE,MAX_FORCE));
    RedSettings.add(sliderRY.setup("RED X YELLOW",force_matrix[RED][YELLOW],-MAX_FORCE,MAX_FORCE));
    sliderRR.setFillColor(ofColor::darkRed);
    sliderRG.setFillColor(ofColor::darkRed);
    sliderRY.setFillColor(ofColor::darkRed);
    RedSettings.add(slider_rangeRR.setup("Radius of RED X RED",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));
    RedSettings.add(slider_rangeRG.setup("Radius of RED X GREEN",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));
    RedSettings.add(slider_rangeRY.setup("Radius of RED X YELLOW",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));

    GreenSettings.setup("GREEN SETTINGS");
    SimSettings.add(&GreenSettings);
    GreenSettings.add(field_number_G.setup("Number of Particles",number_of_particles[GREEN],1,MAX_PARTICLES));
    GreenSettings.add(sliderGR.setup("GREEN X RED",force_matrix[GREEN][RED],-MAX_FORCE,MAX_FORCE));
    GreenSettings.add(sliderGG.setup("GREEN X GREEN",force_matrix[GREEN][GREEN],-MAX_FORCE,MAX_FORCE));
    GreenSettings.add(sliderGY.setup("GREEN X YELLOW",force_matrix[GREEN][YELLOW],-MAX_FORCE,MAX_FORCE));
    sliderGR.setFillColor(ofColor::darkGreen);
    sliderGG.setFillColor(ofColor::darkGreen);
    sliderGY.setFillColor(ofColor::darkGreen);
    GreenSettings.add(slider_rangeGR.setup("Radius of GREEN X RED",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));
    GreenSettings.add(slider_rangeGG.setup("Radius of GREEN X GREEN",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));
    GreenSettings.add(slider_rangeGY.setup("Radius of GREEN X YELLOW",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));

    YellowSettings.setup("YELLOW SETTINGS");
    SimSettings.add(&YellowSettings);
    YellowSettings.add(field_number_Y.setup("Number of Particles",number_of_particles[YELLOW],1,MAX_PARTICLES));
    YellowSettings.add(sliderYR.setup("YELLOW X RED",force_matrix[YELLOW][RED],-MAX_FORCE,MAX_FORCE));
    YellowSettings.add(sliderYG.setup("YELLOW X GREEN",force_matrix[YELLOW][GREEN],-MAX_FORCE,MAX_FORCE));
    YellowSettings.add(sliderYY.setup("YELLOW X YELLOW",force_matrix[YELLOW][YELLOW],-MAX_FORCE,MAX_FORCE));
    sliderYR.setFillColor(ofColor::darkGoldenRod);
    sliderYG.setFillColor(ofColor::darkGoldenRod);
    sliderYY.setFillColor(ofColor::darkGoldenRod);
    YellowSettings.add(slider_rangeYR.setup("Radius of YELLOW X RED",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));
    YellowSettings.add(slider_rangeYG.setup("Radius of YELLOW X GREEN",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));
    YellowSettings.add(slider_rangeYY.setup("Radius of YELLOW X YELLOW",MAX_FORCE_RANGE,0,MAX_FORCE_RANGE));

    gui.add(button_save_settings.setup("Save Simulation"));
    button_save_settings.addListener(this,&ofApp::save_settings);
    gui.add(dropdown.setup("Load Simulation"));
    dropdown.addListener(this,&ofApp::load_settings);
    if (!dropdown.populateFromDirectory(settings_folder_path, {"xml"}))
    ofLogError() << "Could not populate dropdown from path: "+ofToDataPath(settings_folder_path);

    gui.add(field_get_name.setup("Simulation Name:",""));
    feedback.setup("","");
    gui.add(&feedback);

    restart();      // create particles and initialize vectors
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
// Particle constructor
Particle::Particle(const float x, const float y, const float z, const int color)
{
}

// Update particles position based on its updated velocity
void Particle::update(bool toggle) {}

// Force that repells the particles from the edge of the map
// so they do not stay there
void Particle::apply_WallRepel(float force){}

// Calculate the forces that act on this specific particle 
// based on another particle
void Particle::compute_Force(const Particle& acting_particle){}

// Creates a specifc number of every particle type and adds them to the vector of particles
// Every particle is initialized with random positions
void ofApp::Create_particles(){}

// Initialize with random values the forces of interaction between each particle type
void ofApp::initialize_forces(float min, float max){}

// Clears all vectors and creates particles from scratch
void ofApp::restart(){}

// populates the force and force_range matrixes with random values and updates the gui sliders
void ofApp::shuffle(){}

// Save all current Simulation parameters
void ofApp::save_settings(){}

// Load saved settings from a list
// ekteleite 2 fores gia kapoion logo me kathe klik sto dropdown. Einai buggy af to ofxdropdown
void ofApp::load_settings(ofFile &file){}

// Creates a directory for storing all the saved simulation settings
void ofApp::create_settings_dir()
{

}

// Get position vector of particle
glm::vec3 Particle::get_position() const
{
    return this->position;
};

// Get velocity vector of particle
glm::vec3 Particle::get_velocity() const
{
    return this->velocity;
};

// Get type (int) of particle
int Particle::get_type() const
{
    return this->type;
};

// Returns Color of the particle
ofFloatColor Particle::getColor() const{
    if (this->type == 0) {
        return ofFloatColor(1, 0, 0);  // Red
    } else if (type == 1) {
        return ofFloatColor(0, 1, 0);  // Green
    } else {
        return ofFloatColor(1, 1, 0);  // Yellow
    }
}