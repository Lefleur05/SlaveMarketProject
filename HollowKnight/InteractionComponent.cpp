#include "InteractionComponent.h"
#include "Player.h"
#include "ActorManager.h"
#include "InteractableActor.h"
#include "Macro.h"

InteractionComponent::InteractionComponent(Actor* _owner) : Component(_owner)
{
	range = 200.0f;
	inventory = dynamic_cast<Player*>(_owner)->GetInventory();
	merchand = nullptr;
}


void InteractionComponent::TryToInteract()
{
	for (InteractableActor* _interactable : ActorManager::GetInstance().GetInteractables())
	{
		const float _distance = Distance(owner->GetShapePosition(), _interactable->GetShapePosition());
		if (_distance > range) continue;

		if (merchand = dynamic_cast<Merchand*>(_interactable))
		{
			merchand->OpenDiscussion();
		}

		else
		{
			_interactable->OpenDiscussion();
		}

		inventory->SetStatus(false);
	}
}

void InteractionComponent::StopInteract()
{
	if (!merchand) return;
	merchand->CloseDiscussion();
}