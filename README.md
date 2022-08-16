# jni-impl
My own implementation to interact with the JVM.
You can interact with fields and klasses, however Methods are not implemented YET.

## Requirements
A supported JVM version. (some patterns will probably not works on custom JVM)

# Examples
* Get the local player coordinate (Minecraft Java Edition on Lunar Client)
```c
  	auto classLoader = std::make_unique<ClassLoaderData<16>>();
	HookFunction::RunAll();
	classLoader->LoadClasses();

	auto Minecraft = classLoader->FindClass("net/minecraft/v1_8/sesheaeeespaahapeahahahss");
	printf("Minecraft %p\n", Minecraft);
	while (true) {
		auto theMinecraftObj = Minecraft->GetStaticObj(128);
		printf("mcobj %p\n", theMinecraftObj);

		if (theMinecraftObj) {
			auto thePlayer = theMinecraftObj->GetObj(180);
			printf("thePlayer %p\n", thePlayer);

			if (thePlayer) {
				printf("x: %f\n", thePlayer->Get<double>(48));
				printf("y: %f\n", thePlayer->Get<double>(56));
				printf("z: %f\n", thePlayer->Get<double>(64));
			}
		}
		Sleep(1000);
	}
```
