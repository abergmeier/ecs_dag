
class BaseMessage {
};

class OtherSystem {
public:
	static ae::graph::Dag graph() {
		auto dag = ae::graph::Dag();
		dag.nodes.emplace<OtherSystem>(&OtherSystem::update_);
		return dag;
	}
private:
	void update_();
};

class NewSystem {
public:
	static ae::graph::Dag graph();
private:
	void update_():
};

ae::graph::Dag
NewSystem::graph() {
	auto dag = ae::graph::Dag();
#if 0
	// Create message dependency
	auto messageVertex = makeVertex<BaseMessage>();
	auto newUpdateVertex = makeVertex<NewSystem>(&NewSystem::update_);
	dag.emplaceEdge(messageVertex, newUpdateVertex);

	// Create System dependency
	auto otherVertex = makeVertex<Othersystem>(&OtherSystem::update_);
	dag.emplaceEdge(otherVertex, newUpdateVertex);
#endif
	// Alternate
	dag.edges.emplace<BaseMessage, NewSystem>(&NewSystem::update_);
	dag.edges.emplace<OtherSystem, NewSystem>(&OtherSystem::update_, &NewSystem::update_);

	return dag;
}

NewSystem::update_() {
	
}

