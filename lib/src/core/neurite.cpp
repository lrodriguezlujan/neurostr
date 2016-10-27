#include "core/neurite.h"
#include "core/neurite_type.h"
#include "core/log.h"

namespace neurostr {
  
// Constructors

Neurite::Neurite()
      : WithProperties()
      , tree_()  // Call constructor
      , id_(-1)
      , type_(NeuriteType::kUndefined)
      , root_is_soma_(false)
      , neuron_(){
        tree_.head->data.neurite(this);
        tree_.feet->data.neurite(this);
        //set_root();
  };
  
Neurite::Neurite(int id)
      : WithProperties()
      , tree_()  // Call constructor
      , id_(id)
      , type_(NeuriteType::kUndefined)
      , root_is_soma_(false)
      , neuron_(){
        //set_root();
        tree_.head->data.neurite(this);
        tree_.feet->data.neurite(this);
  };
  
Neurite::Neurite(int id, const NeuriteType& t)
      : WithProperties()
      , tree_()  // Call constructor
      , id_(id)
      , type_(t)
      , root_is_soma_(false)
      , neuron_(){
        tree_.head->data.neurite(this);
        tree_.feet->data.neurite(this);
        //set_root();
  };
  
// ROOT SET

// Empty root
void Neurite::set_root() {
  if (tree_.empty()) {    
    // Set branch neurite
    tree_.set_head(Branch(std::vector<int>{1}, 0));
    tree_.begin()->neurite(this);
  } else {
    tree_.begin()->remove_root();
    tree_.begin()->neurite(this);
  }
  
  root_is_soma_ = false;
}

void Neurite::set_root(const Node& node) {
  set_root();
  tree_.begin()->root(node);
  root_is_soma_ = true;
}

int Neurite::node_count() const {
    int count = 0;
    for (auto it = begin_branch(); it != end_branch(); it++) count += it->size();
    return count;
}


Neurite::branch_iterator Neurite::end_branch_subtree(
  const typename Neurite::tree_type::iterator_base& other) const {
    tree_node* tn = other.node;

    if (tn == nullptr)
      return Neurite::branch_iterator(other);
    else {
      while (tn->next_sibling == nullptr) {
        tn = tn->parent;
        if (tn == nullptr) return Neurite::branch_iterator(tn);
      }
      // The next "node"
      return Neurite::branch_iterator(tn->next_sibling);
    }
}


// Node - based function
Neurite::base_node_iterator Neurite::insert_node(Node::id_type parent_id, const Node& node) {
  if (parent_id == -1) {
    if (!tree_.empty()) throw std::runtime_error("");
    return insert_node(end_node(), node);
  }
  auto it = find(parent_id);
  if (it.branch().node == tree_.feet)  // Not found
    throw std::runtime_error("");
  else
    return insert_node(it, node);
}

void Neurite::correct()  {
    bool trigger = false;
    typename tree_type::sibling_iterator ch;
    
    // Collapse single-child branches
    for (branch_iterator it = begin_branch(); it != end_branch(); ++it) {
      if (it.number_of_children() == 1) {

        NSTR_LOG_(info) << "Removing single-childed branch in neurite " << id();
        
        // Single children nodes -> collapse
        trigger = true;
        ch = it.begin();

        // Copy elements in ch except for the root
        for(auto chit = ch->begin() ; chit != ch->end() ; ++chit){
          it->push_back(*chit);
        }
        //it->insert(it->end(), ch->begin(), ch->end());

        // Reparent nodes
        tree_.reparent(it, ch.begin(), ch.end());

        // Remove ch
        tree_.erase(ch);
      }
    }
    // Reassign branch ids + order
    if (trigger) reassign_branch_ids();
};

void Neurite::remove_null_segments() {
  for(auto it = begin_branch(); it != end_branch() ; ++it){
    it->remove_null_segments();
  }
}

// Scale
void Neurite::scale(float r){
  // Scale all branches
  for( auto it = tree_.begin_post(); it != tree_.end_post() ; ++it ) {
    // We are using post_order iterator. Children are always scaled before parents
    
    // Scale this branch
    it->scale(r);
    
    // Set child root (child is already scaled) :D
    for( auto chit = tree_.begin(it); chit != tree_.end(it); ++chit )
      chit->root(it->last());
  }
}

void Neurite::scale(float rx, float ry, float rz){
  for( auto it = begin_branch(); it != end_branch() ; ++it ) {
    it->scale(rx,ry,rz);
  }
}

/**
   * @brief Normalizes all branches in the neurite
   */
void Neurite::normalize_branches(){
  // Normalize all branches
  for( auto it = begin_branch(); it != end_branch() ; ++it ) {
    it->normalize();
  }
  
  // Join roots
  for( auto it = begin_branch(); it != end_branch() ; ++it ) {
    for( auto chit = tree_.begin(it); chit != tree_.end(it); ++chit){
      chit->traslate(chit->root().vectorTo(it->last()));
    }
  }
    
}

// Traslate
void Neurite::traslate(const point_type& p){
  for( auto it = tree_.begin(); it != tree_.end() ; ++it ) {
    it->traslate(p);
  }
}

// Rotate
void Neurite::rotate(const Eigen::Quaternionf& q){
  for( auto it = tree_.begin(); it != tree_.end() ; ++it ) {
    it->rotate(q);
  }
}

void Neurite::simplify(float eps) {
  for( auto it = tree_.begin(); it != tree_.end() ; ++it ) {
    it->simplify(eps);
  }
}

Neurite::branch_iterator Neurite::find(const Branch& b) const{
  for( auto it = tree_.begin(); it != tree_.end() ; ++it ) {
    if(*it == b) return it;
  }
  return tree_.end();
}

/* TODO
 * void Neurite::childOrder(){
  for( auto it = tree_.begin(); it != tree_.end() ; ++it ) {
    // Order its children (only standard 2ch case)
    if(it.number_of_children() == 2){
      auto ch1 = begin_children(it);
      auto ch2 = ch1; ++ch2;
      // IF azimuth of ch1 is > azimuth of ch2 .. swap
      if( measures::branch::branch_azimuth( branch_reference(this, ch1) ) > 
          measures::branch::branch_azimuth( branch_reference(this, ch2) ) )
            tree_.swap(ch1,ch2);
    }
  }
}*/



int Neurite::max_centrifugal_order() const{
  
  int maxOrder = -1;
  for( auto it = begin_leaf(); it != end_leaf() ; ++it){
    if(it->order() > maxOrder) maxOrder = it->order();
  }
  return maxOrder;
}

void Neurite::reassign_branch_ids() {
    // Empty check
    if (tree_.empty())
      return;
    else {  // reassign root id
      begin_branch()->id(std::vector<int>{1});
      begin_branch()->order(0);
    }

    std::vector<int> tmp;

    // Iterate over the tree rassigning ids
    for (auto it = ++begin_branch(); it != end_branch(); ++it) {
      tmp = tree_type::parent(it)->id();                                         // Get parent id
      tmp.push_back(tree_.index(typename tree_type::sibling_iterator(it)) + 1);  // add our position to the id
      it->id(tmp);                                                               // set id
      it->order(tree_type::parent(it)->order() + 1);                             // set order
    }
};

bool Neurite::remove_empty_branches(){
  
  bool trigger = false;
  typename tree_type::sibling_iterator ch;
    
  // Collapse single-child branches
  for (branch_iterator it = begin_branch(); it != end_branch(); ++it) {
    if (it->size() == 0) {
        // Single children nodes -> collapse
        if(it.node->parent == nullptr){
          // we are the first branch
          NSTR_LOG_(warning) << "Cannot remove empty root branch in neurite " << id();
        } else {
          trigger = true;  
          NSTR_LOG_(info) << "Removing empty branch" << it->idString() <<" in neurite " << id();
          // We assing our children to the parent node.
          if(it.number_of_children()>0){
            tree_.reparent(tree_type::parent(it), it.begin(), it.end());
          }
          // Erase branch
          it = std::prev(tree_.erase(it),1);
        }
      }
  }
  return trigger;
}

bool Neurite::collapse_single_branches(){
  bool trigger = false;
  typename tree_type::sibling_iterator ch;
    
  // Collapse single-child branches
  for (branch_iterator it = begin_branch(); it != end_branch(); ++it) {
    if (it.number_of_children() == 1) {

        NSTR_LOG_(info) << "Removing single-childed branch" << it->idString() <<" in neurite " << id();
        
        // Single children nodes -> collapse
        trigger = true;
        ch = it.begin();

        // Copy elements in ch except for the root
        for(auto chit = ch->begin() ; chit != ch->end() ; ++chit){
          it->push_back(*chit);
        }
        //it->insert(it->end(), ch->begin(), ch->end());

        // Reparent nodes
        tree_.reparent(it, ch.begin(), ch.end());

        // Remove ch
        tree_.erase(ch);
        
        // Update it so we check it again
        it = std::prev(it,1);
      }
    }
    return trigger;
}

void Neurite::reassign_branch_roots(){
  
  if(size() <= 1) return;
  
  for( auto it = std::next(begin_branch(),1); it != end_branch(); ++it){
    if(tree_type::parent(it)->size() > 0){
      it->root(tree_type::parent(it)->last());
    } else if (tree_type::parent(it)->has_root()){
      it->root(tree_type::parent(it)->root());
    } else {
      NSTR_LOG_(warning) << "Can't find a suitable root for branch " << it->idString();
    }
  }
}

void Neurite::invalidate_node_cached_values(){
  // nodes
  for(auto it = begin_node(); it != end_node(); ++it){
    it->invalidate_basis();
    it->invalidate_length();
  }
  
  // Then root
  for(auto it = begin_branch(); it != end_branch(); ++it){
    if(it->has_root()){
      it->root().invalidate_basis();
      it->root().invalidate_length();  
    }
  }
  
}

std::ostream& operator<<(std::ostream& os, const Neurite& n) {

    // Print * line
    os << std::string(50, '*') << std::endl;

    // Print ID:
    os << "Neurite ID: " << n.id_ << std::endl;
    /// Type
    os << "Type: " << n.type_ << std::endl;
    // Root attached to soma
    os << "Root is attached to soma: " << n.root_is_soma() << std::endl;
    // Number of nodes
    os << "Node count: " << n.node_count() << std::endl;
    // Print metadata/properties
    if (n.properties.size() > 0) {
      os << "Properties: " << std::endl;
      for (auto it = n.properties.begin(); it != n.properties.end(); ++it) {
        if (it->second.empty())
          os << "\t" << it->first << std::endl;
        else if (it->second.type() == typeid(float))
          os << "\t" << it->first << ": " << boost::any_cast<float>(it->second) << std::endl;
        /*else if (it->second.type() == typeid(neurostr::io::nl::tree_type_cd))
          os << "\t" << it->first << ": " << boost::any_cast<neurostr::io::nl::tree_type_cd>(it->second) << std::endl;*/
        else if (it->second.type() == typeid(NeuriteType))
          os << "\t" << it->first << ": " << boost::any_cast<NeuriteType>(it->second) << std::endl;
        else
          os << "\t" << it->first << ": " << boost::any_cast<std::string>(it->second) << std::endl;
      }
    }

    // Print content
    if (n.size() > 0) {
      for (auto it = n.begin_branch(); it != n.end_branch(); ++it) {
        os << (*it) << std::endl;
      }
    }

    os << std::string(50, '*') << std::endl;

    return os;
};

// STEM ITERATOR


    Neurite::stem_iterator::stem_iterator() 
      : tree_type::iterator_base() {};
      

    Neurite::stem_iterator::stem_iterator(tree_node* tn) 
      : tree_type::iterator_base(tn) {};
      

    Neurite::stem_iterator::stem_iterator(
      const typename Neurite::tree_type::iterator_base& other) 
      : tree_type::iterator_base(other.node) {};


    bool Neurite::stem_iterator::operator==(const Neurite::stem_iterator& other) const {
      return (this->node == other.node);
    };
    
    bool Neurite::stem_iterator::operator!=(const Neurite::stem_iterator& other) const {
      return (this->node != other.node);
    };


    Neurite::stem_iterator& Neurite::stem_iterator::operator++() {
      assert(this->node != nullptr);
      if(this->node->parent == nullptr){
        assert(this->node->prev_sibling != nullptr);
        this->node = this->node->prev_sibling;
      } else
        this->node = this->node->parent;
      return *this;
    };


    Neurite::stem_iterator Neurite::stem_iterator::operator++(int) {
      stem_iterator copy = *this;
      ++(*this);
      return copy;
    };


    Neurite::stem_iterator& Neurite::stem_iterator::operator+=(unsigned int num) {
      while (num > 0) {
        ++(*this);
        num--;
      }
      return *this;
    };



}  // namespace neurostr
