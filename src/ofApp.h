#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"

constexpr short MAP_BORDER = 10;     // This is used so the particles can not be on the edge of the screen for better visibility 
constexpr float MAX_FORCE = 50;
constexpr short MAX_FORCE_RANGE = 200;
constexpr float WALL_REPEL_FORCE_MAX = 10;
constexpr short WALL_REPEL_BOUND = MAP_BORDER+4;  // the wall starts repelling particles if they're closer than WALL_REPEL_BOUND pixels
constexpr short MAX_PARTICLES = 3000;
constexpr short NUM_TYPES = 3;        // Number of different particle types
const string settings_folder_path = "Settings";         //relative to bin/data

#define RED 0
#define GREEN 1
#define YELLOW 2

class Particle
{
private:
	//glm vector -> better performance for graphics apperantly
	glm::vec3 position;		// 3D vector representing the position (x, y)
	glm::vec3 velocity;		// 3D vector representing the velocity (vx, vy)
	int type;				// Type of the particle (for interaction rules)
public:
	Particle(const float x, const float y, const float z, const int color);
	void update(const bool toggle);
	void apply_WallRepel(const float force);
	void compute_Force(const Particle& acting_particle);
	
	glm::vec3 get_position() const;
	glm::vec3 get_velocity() const;
	int get_type() const;
	ofFloatColor getColor() const;
};



class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;

		void keyPressed(int key) override;

		vector<Particle> all_particles;		// vector containing all particles;
		vector<glm::vec3> all_positions;	// this is needed for the vbo	
		vector<ofFloatColor> all_colors;  	// also for vbo

		void Create_particles();
		void initialize_forces(const float min, const float max);
		void initialize_color_force_range(const short min, const short max);
		void restart();
		void shuffle();
		void save_settings();
		void create_settings_dir();
		void load_settings(ofFile &file);
	
	ofxPanel gui;
	ofxGuiGroup RedSettings, GreenSettings, YellowSettings, SimSettings;
	ofxButton button_restart, button_shuffle, button_save_settings;
	ofxToggle  toggle_shuffle_numbers, toggle_shuffle_radi;
	ofxFloatSlider	sliderRR,sliderRG,sliderRY, sliderGR,sliderGG,sliderGY, sliderYR,sliderYG,sliderYY, 
					slider_viscosity, slider_wall_repel_force;
	ofxIntSlider slider_rangeRR, slider_rangeRG, slider_rangeRY,
				 slider_rangeGR, slider_rangeGG, slider_rangeGY, slider_rangeYR, slider_rangeYG, slider_rangeYY;
	ofxIntField field_number_G, field_number_Y,field_number_R;
	ofVbo vbo;								// more efficient batch drawing

	ofxDirDropdown dropdown;
	ofxInputField<string> field_get_name;	// input field to enter the name for saving the settings
	ofxLabel feedback;

	ofEasyCam cam;
	
};
