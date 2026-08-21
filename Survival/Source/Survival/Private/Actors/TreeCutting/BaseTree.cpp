// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TreeCutting/BaseTree.h"

ABaseTree::ABaseTree()
{
	PrimaryActorTick.bCanEverTick = true;

	TreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh"));
	SetRootComponent(TreeMesh);
}

