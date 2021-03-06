#ifndef __AnimationPlayer__
#define __AnimationPlayer__

#include "Mesh.h"
#include "SkeletalAnimation.h"

class AnimationPlayer
{
public:
	AnimationPlayer();
	virtual ~AnimationPlayer();

	void Init(std::string meshPath, std::string animationPath);

	void Play(float delta);

	bool IsSet() const;

	float ClipLength() const;

	std::pair<std::string, SkeletalAnimation*>	Animation;	
    std::vector<unsigned char>					ChannelMap;
    std::vector<cFBXBuffer::JointPose>			CurrentBones;

	XMFLOAT4X4				mPrevRoot;	
    XMFLOAT3                mRootTranslation;
    XMFLOAT4                mRootRotation;

	float GetCurrentPhase();
	void SetCurrentPhase(float);

	float                   AnimTime;
    float                   AnimRate;
    std::size_t             CurrentFrame;
	std::size_t             PreviousFrame;
};

#endif // __AnimationPlayer__