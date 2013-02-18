//////////////////////////////////////////
///           IEngine.cpp
//////////////////////////////////////////

int mouse_x = 0;
int mouse_y = 0;
float gl_x = 0;
float gl_y = 0;

#include "IEngine.h"

#include <stdlib.h>

IEngine::IEngine(int argc, char** argv)
{
	printf("Initializing IEngine\n");
	initGL(argc, argv);
	
	window_dim = GLWindow::getInstance();
	
	window_dim->m_width = 800;
	window_dim->m_height = 600;
	
	
	resize(window_dim->m_width, window_dim->m_height);
	m_time = 0.0;
	frames = 0;
	m_updateRate = 1/60.0;

	running = true;

	//ext crap
	
	glEnable(GL_TEXTURE_2D);
	AssetPool::getInstance()->loadTexture("exhaust");
	AssetPool::getInstance()->loadTexture("metal");
	shot_tex = Texture::loadTexture((char*)"tex");
	ship_tex = Texture::loadTexture((char*)"star");
	shit_tex = Texture::loadTexture((char*)"tex3");
	
	Text::initialize();
	
	game = GameSpace::getInstance();

	mouseCoords = vec2(0,0);
	
	info = InfoText::getInstance();
		
	shot_count = 0;
	
 	p = ParticleEngine::getInstance();
 	
 	SoundEngine * sengine = SoundEngine::getInstance();
 	
 	sengine->loadSoundFile("gun.wav");
 	sengine->loadSoundFile("engine.wav");
	
	AssetPool::getInstance()->loadDrawable("cube","plain");
	AssetPool::getInstance()->loadDrawable("ship","plain");
	AssetPool::getInstance()->loadDrawable("cannon","plain");
	AssetPool::getInstance()->loadDrawable("wing","plain");
	AssetPool::getInstance()->loadDrawable("cockpit","plain");
	AssetPool::getInstance()->loadDrawable("engine2","plain");
	
	s = new Shader("shaders/stars.vs", "shaders/stars.fs");
	
	cd = new CollectionDrawable(s->getID());
	
	if (int err = glGetError()){
		fprintf(stderr, "error in init: %s\n", gluErrorString(err));
		exit(0);
	}
	
	game->player = game->ship_pool->getObject();
	game->player->init();
	game->player->setTurnDamping(.005);
	game->player->setAsPlayer();
	game->player->setFaction(0);
	
	for (int i = 0; i < 50; i++){
		Ship * ship = game->ship_pool->getObject();
		ship->init();
		
		int faction = 1;
		ship->setFaction(faction);
		ship->setPos(randCircle(vec2(0,0),200) + randSpread(vec2(0,0), 200));
	}
	
	cooldown = 0;
	
	offset = 0;
	
	info->addString((char*)"===============");
	info->addString((char*)"======derp=====");
	info->addString((char*)"===============");
	
	info->addString((char*)"w/s accel/decel");
	info->addString((char*)"a/d rotate");
	info->addString((char*)"'['/']' zoom out/in");
	info->addString((char*)"space fire");
	info->addString((char*)"q autoaim");
	info->addString((char*)"nothing to do except get shot at");
	
	want_to_quit = 0;
	
	cameraPos.z = 500;
	cameraPos.x = 0;
	cameraPos.y = 0;
	
	
	//	
	
}

void IEngine::initGL(int argc, char** argv)
{
	m_window = new sf::Window(sf::VideoMode(800,600, 32), "IEngine");
	m_clock = new sf::Clock();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPointSize(1.1);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(3.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	if (int err = glGetError()){
		fprintf(stderr, "error in initgl: %s\n", gluErrorString(err));
		exit(0);
	}
}


void IEngine::checkKeys(){

	
	const sf::Input& input = m_window->GetInput();
	
	float mx = input.GetMouseX();
	float my = input.GetMouseY();
	
	// Convert pixel space into (1*ratio,-1*ratio,1,-1) unit space
	//mx = 2*(mx - m_width / 2.0) / m_width * m_width_ratio;
	//my = -2*(my - m_height / 2.0) / m_height;
	
	// Convert into gl unit space
	//mx = mx * 5.0;
	//my = my * 5.0;
	
	mouseCoords.x = mx;
	mouseCoords.y = my;
	mb = MB_NONE;
	bool lbutton = input.IsMouseButtonDown(sf::Mouse::Left);
	bool rbutton = input.IsMouseButtonDown(sf::Mouse::Right);
	
	if (lbutton){
		mb = MB_LEFT;
	}
	if (rbutton){
		mb = MB_RIGHT;
	}
	
	bool space = input.IsKeyDown(sf::Key::Space);
	
	bool up = input.IsKeyDown(sf::Key::Up);
	bool down = input.IsKeyDown(sf::Key::Down);
	bool right = input.IsKeyDown(sf::Key::Right);
	bool left = input.IsKeyDown(sf::Key::Left);
	
	bool shift = input.IsKeyDown(sf::Key::LShift);
	
	bool lbrack = input.IsKeyDown(sf::Key::LBracket);
	bool rbrack = input.IsKeyDown(sf::Key::RBracket);
	
	bool w = input.IsKeyDown(sf::Key::W);
	bool d = input.IsKeyDown(sf::Key::D);
	bool s = input.IsKeyDown(sf::Key::S);
	bool a = input.IsKeyDown(sf::Key::A);
	
	bool q = input.IsKeyDown(sf::Key::Q);
	
	double x, y;
	sincos(game->player->getRot(), &y, &x);
	
	
	if (lbrack){
		cameraPos.z ++;
	}
	
	if (rbrack){
		cameraPos.z --;
	}
	
	if(q){
		game->player->stabilize();
	}
	
	SoundEngine * sengine = SoundEngine::getInstance();
	sengine->setListenerPosition(game->player->getPos().x, game->player->getPos().y);
	sf::Listener::SetTarget(0,0,100);
	static int engine_noise = sengine->loadSound("engine.wav", true);
	static int playing = 0;
	if (w){
		float amount = 1.0;
		if (shift) amount *=2;
		game->player->accelerate(amount);
		if (!playing){
			sengine->playSound(engine_noise);
			sengine->setVolume(engine_noise, 200);
		}
		playing = 1;
		
	}

	else {
		sengine->stopSound(engine_noise);
		playing = 0;
	}
	
	if (s){
		game->player->accelerate(-.5);
	}
	
	if (a){
		game->player->turn(.02);

	}
	
	if (d){
		game->player->turn(-.02);
		

		
	}
	static int shot_noise = sengine->loadSound("gun.wav");
	
	if (space){
			game->player->fire();
			//sengine->playSound(shot_noise);
			//sengine->setPosition(shot_noise, 100, 0);
	}

}

int IEngine::begin()
{
	while(m_window->IsOpened())
	{
		if (!running){
			m_window->Close();
			return 0;
		}
		sf::Event Event;
		while(m_window->GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
			{
				m_window->Close();
				return 0;
			}
			
			else if(Event.Type == sf::Event::KeyPressed)
			{
				// For one-press keys: (starts to repeat after a while)
				if(Event.Key.Code == sf::Key::Escape)
				{
					if (!want_to_quit) {
						info->addString("Are you sure? Esc again to quit.", ALERT);
						want_to_quit = 120;
					}
					else{
						m_window->Close();
						return 0;
					}
				}
			}
			else if(Event.Type == sf::Event::MouseWheelMoved){
				cameraPos.z += -Event.MouseWheel.Delta * cameraPos.z * .1;
			}
			else if(Event.Type == sf::Event::Resized)
			{
				resize(Event.Size.Width, Event.Size.Height);
			}
			
		}
		
		checkKeys();
		
		update();
		
		drawScene();
		
		m_window->Display();
	}
	return 0;
}


void IEngine::drawScene()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,window_dim->m_width_ratio,5,10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float dmg_x_offset = offset * cos(frames);
	float dmg_y_offset = offset * sin(frames);

	
	vec2 ppos = game->player->getPos();
	
	cameraPos.x = ppos.x;
	cameraPos.y = ppos.y;

	glPushMatrix();
	glTranslatef((-cameraPos.x + dmg_x_offset) * .002, (-cameraPos.y + dmg_y_offset) * .002 , -(cameraPos.z + dmg_x_offset)*.002);
	glBindTexture(GL_TEXTURE_2D, ship_tex);
	
	s->bind();
	
	cd->draw();
	
	s->release();

	glPopMatrix();
	
	glRotatef(-30,1,0,0);
	glTranslatef((-cameraPos.x), (-cameraPos.y + .7*cameraPos.z), (-cameraPos.z));
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, shit_tex);
	glDisable(GL_BLEND);
	p->draw();
	glEnable(GL_BLEND);
	
	glBindTexture(GL_TEXTURE_2D, shot_tex);
	glEnable(GL_DEPTH_TEST);
	game->draw();
	glDisable(GL_DEPTH_TEST);
	
	glDisable(GL_TEXTURE_2D);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0 * window_dim->m_width_ratio,5.0 * window_dim->m_width_ratio,-5.0,5.0,-5.0,5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	std::vector<Weapon *> weapons = game->player->getWeapons();
	for (int i = 0; i < weapons.size(); i++){
		float ratio = weapons[i]->getCooldown()/ (float)weapons[i]->getFireRate();
		float max = 1.0;
		glColor3f(.3,.3,.3);
		
		glBegin(GL_TRIANGLES);
		glVertex2f(-5*window_dim->m_width_ratio, .05 + i*.1);
		glVertex2f(-5*window_dim->m_width_ratio, i*.1);
		glVertex2f(-5*window_dim->m_width_ratio+max, i*.1);
	
		glVertex2f(-5*window_dim->m_width_ratio, .05+i*.1);
		glVertex2f(-5*window_dim->m_width_ratio+max, .05+i*.1);
		glVertex2f(-5*window_dim->m_width_ratio+max, i*.1);
		glEnd();	
		
		glColor3f(1.0,1.0,1.0);
		
		if (weapons[i]->isOverheating()){
			glColor3f(1.0,0,0);
		}
		else if (ratio > .8){
			glColor3f(1.0,.5,.0);
		}
		else if (ratio > .6){
			glColor3f(1.0,.7,.2);
		}
		else if (ratio > .4){
			glColor3f(1.0,.8,.6);
		}
		
		
		glBegin(GL_TRIANGLES);
		glVertex2f(-5*window_dim->m_width_ratio, .05 + i*.1);
		glVertex2f(-5*window_dim->m_width_ratio, i*.1);
		glVertex2f(-5*window_dim->m_width_ratio+ratio*max, i*.1);
	
		glVertex2f(-5*window_dim->m_width_ratio, .05+i*.1);
		glVertex2f(-5*window_dim->m_width_ratio+ratio*max, .05+i*.1);
		glVertex2f(-5*window_dim->m_width_ratio+ratio*max, i*.1);
		glEnd();	
	}
	
	glColor4f(0,0,.1, .6);
	glBegin(GL_TRIANGLES);
	glVertex2f(-5*window_dim->m_width_ratio, -5);
	glVertex2f(-5*window_dim->m_width_ratio, -5+.15*21);
	glVertex2f(-1*window_dim->m_width_ratio, -5+.15*21);
	
	glVertex2f(-5*window_dim->m_width_ratio, -5);
	glVertex2f(-1*window_dim->m_width_ratio, -5);
	glVertex2f(-1*window_dim->m_width_ratio, -5+.15*21);
	glEnd();
	
	Text::bind();
	Text::setScale(.15);
	int pos = 0;
	std::vector<info_string*> infotext = info->getStrings();
	int num_strings = info->getMaxStringIndex();
	int start_index = (num_strings > 20 ? num_strings-20 : 0);
	for (int i = start_index; i < infotext.size(); i++){
		info_string * t = infotext[i];
		if (t->dead) continue;
		Text::setColor(t->color);
		Text::renderString(-5 *window_dim->m_width_ratio + .15, -(pos*.15) - (5.0 - .15 * 20) + .15, t->str);
		pos ++;
	}
	
	char str[64];
	float white[] = {1,1,1};
	Text::setColor(white);
	sprintf(str, "%i fps", (int)fps);
	Text::setScale(.5);
	Text::renderString(2,4,str);
	
	Text::setScale(.2);
	sprintf(str, "Current speed: %3.3f", game->player->getVel().length());
	Text::renderString(0,-3, str);
	
	Text::unbind();
	
}


void IEngine::update()
{
	float newTime = m_clock->GetElapsedTime();
	float diff = newTime-time;
	
	float multiplier = 1.0;
	
	while(diff < m_updateRate)
	{
		newTime = m_clock->GetElapsedTime();
		diff = newTime-time;
    	continue;
    }
    time = newTime;

   	if(diff > m_updateRate)
	{
		multiplier = time / m_updateRate;
	}
	
	if ((frames%10)==0){
		fps = int(1.0/diff);
	}
	
	frames++;
	
	// ext crap
	
	if (want_to_quit > 1){
		want_to_quit --;
	}
	else if (want_to_quit == 1){
		info->addString("Press Esc again twice to quit.", ALERT);
		want_to_quit = 0;
	}
	
	game->update();
	p->update();
	if (cooldown>0){
		cooldown--;
	}
	if (offset > .1){
		offset -=.1;
	}
	else if (offset > 0){
		offset = 0;
	}
	//w.checkMouse(mouseCoords, mb);
	
	//
}

void IEngine::resize(int width, int height)
{

	window_dim->m_width_ratio = (height>0) ? (GLfloat)width/height : 1;
	window_dim->m_width = width;
	window_dim->m_height = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,window_dim->m_width_ratio,5,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
