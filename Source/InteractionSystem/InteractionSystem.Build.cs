// Copyright 2024 Thieves of the Night. All Rights Reserved.

using UnrealBuildTool;

public class InteractionSystem : ModuleRules
{
	public InteractionSystem(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
			
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
			}
		);
			
		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GameplayAbilities",
				"GameplayTags",
			}
		);
	}
}
