# AINodeGraph
Simple AI Task/State Machine and NodeGraph editor for runtime implementation. Slightly depending on our schools proprietary engine, "Tengine". Fully dependant on ImGui and ImNodes.

Any use of these codes outside of Tengine will require slight source modifications of varibale types.

![image](https://cdn.discordapp.com/attachments/875515865540472842/1038064190889394196/image.png)

## How to use AIBrain

Inherit your AI from AIBrain, example:


```cpp
class CEnemy : public AIBrain
```

Create Tasks for your AI, these will execute logic on tick and return either true or false so it can be setup in a similar fashion to ImGui.

Initialize your tasks in your AIBrain child class like this:

```cpp
Header:
MyChildAITask* ChildAITask;

Cpp constructor:
InitTask(ChildAITask = new MyChildAITask(this, "MyTaskName"));
```

Then you can either just use these in your update function, if you want to use the NodeGraph then skip this step.

This can look something like this:

```cpp
In Update/Tick Function:
if(ExecuteTask(FindPlayerTask))
    ExecuteTask(PathToPlayerTask);
ExecuteTask(PatrolRandomlyTask);
```

## How to use AI Node Graph

Initialize a new AINodeGraph instance somewhere, and run ```cpp DrawAIGraph();``` in a Tick/Update function.

Now you'll see the NodeGraph.

If you want to create new nodes, look at AINodeObject class. It has virtual functions that you have to override to give it functionality. Check "AINode_Task", "AINode_Sequence" or "AINode_Start" for reference.

The last step is to modify AINodeGraph.cpp' "NODE SPAWN BUTTONS" section to make an ImGui button to spawn your node.
