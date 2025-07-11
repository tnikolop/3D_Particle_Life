#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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