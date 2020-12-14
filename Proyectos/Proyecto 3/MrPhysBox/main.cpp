#include <Box2D/include/box2d.h>
#include "Simulation.h"

int main(int argc, char* args[])
{
	const float FPS = 60;
	const float frameDelay = 1000 / FPS;

	Uint32 frameStart;
	Uint32 frameEnd;
	float frameTime = 0.0f;

	Simulation* simulation = nullptr;
	simulation = new Simulation();
	simulation->init("Box2D Test", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 640, 360, false);

	/*
		PIXEL PER METER VALUE
	*/

	float ppm = 64.0f;

	/*
		CREAR EL WORLD USANDO EL CONSTRUCTOR CORRECTO DONDE SE DEFINE LA GRAVEDAD.
	*/

	b2World gameWorld(b2Vec2(0.0f, 10.0f));



	/*
		CREACION DEL CONTACT LISTENER
	*/

	MyContactListener mainListener;
	gameWorld.SetContactListener(&mainListener);

	/*
		CREACION DEL PERSONAJE
	*/

	b2BodyDef charBodyDef;
	charBodyDef.position.Set(100.0f / ppm, 100.0f / ppm);
	charBodyDef.type = b2_dynamicBody;

	b2Body* charBody = gameWorld.CreateBody(&charBodyDef);

	b2PolygonShape charBox;
	charBox.SetAsBox(20.0f * 0.5f / ppm, 54.0f * 0.5f / ppm);

	b2FixtureDef charBodyFixtures;
	charBodyFixtures.shape = &charBox;
	charBodyFixtures.density = 1.0f;
	charBodyFixtures.friction = 0.0f;

	charBody->CreateFixture(&charBodyFixtures);
	charBody->SetFixedRotation(true);

	
	//SENSOR DE PERSONAJE
	charBodyFixtures.isSensor = true;
	b2Fixture* sensorFixture = charBody->CreateFixture(&charBodyFixtures);
	b2FixtureUserData *sensor_data = &sensorFixture->GetUserData();
	sensor_data->pointer = 10; 


	/*
	CREACION DEL PISO
	*/

	b2BodyDef floorDef;
	floorDef.position.Set(320.0f / ppm, 348.0f / ppm);

	b2Body* floorBody = gameWorld.CreateBody(&floorDef);

	b2PolygonShape floorBox;
	floorBox.SetAsBox(640.0f * 0.5f / ppm, 24.0f * 0.5f / ppm);

	b2FixtureDef floorFixtures;
	floorFixtures.shape = &floorBox;
	floorFixtures.density = 0.0f;

	floorBody->CreateFixture(&floorFixtures);

	/*
		CREAMOS EL SENSOR DEL SUELO
	*/
	floorFixtures.isSensor = true;
	b2Fixture* FloorSensorFixture = floorBody->CreateFixture(&floorFixtures);
	b2FixtureUserData* floor_sensor_data = &FloorSensorFixture->GetUserData();
	floor_sensor_data->pointer = 5;

	/*
		CRACION DE PLATAFORMA 1
	*/

	b2BodyDef plat1Def;
	plat1Def.position.Set(96.0f / ppm, 240.0f / ppm);

	b2Body* plat1Body = gameWorld.CreateBody(&plat1Def);

	b2PolygonShape plat1Box;
	plat1Box.SetAsBox(160.0f * 0.5f / ppm, 32.0f * 0.5f / ppm);

	b2FixtureDef plat1Fixtures;
	plat1Fixtures.shape = &plat1Box;
	plat1Fixtures.density = 0.0f;

	plat1Body->CreateFixture(&plat1Fixtures);

	/*
		SENSOR DE PLAT1
	*/
	plat1Fixtures.isSensor = true;
	b2Fixture* plat1SensorFixture = plat1Body->CreateFixture(&plat1Fixtures);
	b2FixtureUserData* plat1_sensor_data = &plat1SensorFixture->GetUserData();
	plat1_sensor_data->pointer = 1;

	/*
		CREACION DE PLATAFORMA 2
	*/

	b2BodyDef plat2Def;
	plat2Def.position.Set(320.0f / ppm, 160.0f / ppm);

	b2Body* plat2Body = gameWorld.CreateBody(&plat2Def);

	b2PolygonShape plat2Box;
	plat2Box.SetAsBox(96.0f * 0.5f / ppm, 32.0f * 0.5f / ppm);

	b2FixtureDef plat2Fixtures;
	plat2Fixtures.shape = &plat2Box;
	plat2Fixtures.density = 0.0f;

	plat2Body->CreateFixture(&plat2Fixtures);

	/*
		SENSOR DE PLAT2
	*/
	plat2Fixtures.isSensor = true;
	b2Fixture* plat2SensorFixture = plat2Body->CreateFixture(&plat2Fixtures);
	b2FixtureUserData* plat2_sensor_data = &plat2SensorFixture->GetUserData();
	plat2_sensor_data->pointer = 2;

	/*
		CREACION DE PLATAFORMA 3
	*/

	b2BodyDef plat3Def;
	plat3Def.position.Set(560.0f / ppm, 112.0f / ppm);

	b2Body* plat3Body = gameWorld.CreateBody(&plat3Def);

	b2PolygonShape plat3Box;
	plat3Box.SetAsBox(128.0f * 0.5f / ppm, 32.0f * 0.5f / ppm);

	b2FixtureDef plat3Fixtures;
	plat3Fixtures.shape = &plat3Box;
	plat3Fixtures.density = 0.0f;

	plat3Body->CreateFixture(&plat3Fixtures);

	/*
		SENSOR DE PLAT3
	*/

	plat3Fixtures.isSensor = true;
	b2Fixture* plat3SensorFixture = plat3Body->CreateFixture(&plat3Fixtures);
	b2FixtureUserData* plat3_sensor_data = &plat3SensorFixture->GetUserData();
	plat3_sensor_data->pointer = 3;


	/*
		INICIA LA SIMULACIÓN.
	*/

	while (simulation->running()) {
		frameStart = SDL_GetTicks();

		simulation->handleEvents(charBody, mainListener.onAir);
		simulation->update(charBody->GetPosition().x * ppm, charBody->GetPosition().y * ppm);
		simulation->render();

		/*
			AQUÍ VA EL STEP() DEL WORLD.
		*/

		gameWorld.Step(frameTime / 1000.0f, 6, 2);

		/*
			SE CALCULA EL FRAMETIME Y SE CORRIGE EL FRAMERATE SI ES NECESARIO.
		*/

		frameEnd = SDL_GetTicks();
		frameTime = frameEnd - frameStart;

		if (frameTime < frameDelay)
		{
			SDL_Delay(frameDelay - frameTime);
		}

		frameTime = SDL_GetTicks() - frameStart;
	}

	simulation->clean();

	return 0;
}