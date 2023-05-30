#pragma once
class SolarSystem : public Scene
{
public:
	SolarSystem();
	virtual ~SolarSystem();

	virtual void Update() override;
	virtual void Render() override;



private:
	shared_ptr<Quad> _sun;
	shared_ptr<Quad> _earth;
};

