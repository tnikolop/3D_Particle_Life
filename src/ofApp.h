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
	glm::vec3 get_type() const;
	ofFloatColor getColor() const;

};

Particle::Particle(float x, float y, float z, int color)
{
}


class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;

		void keyPressed(int key) override;
	
};
