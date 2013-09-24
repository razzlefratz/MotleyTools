/*====================================================================*
 *
 *   oqueue.cpp - implementation of the oqueue class.
 *
 *   this object implements a dequeue; objects may be added or removed 
 *   from either end; A LIFO or stack can be implemented by adding and
 *   removing from one end only. A FIRO or queue can be implemented by
 *   adding to one end and removing from the other end only.
 *
 *   oqueue->insert(void *object) adds an item to the head of the dequeue.
 *   oqueue->append(void *object) adds an item to the tail of the dequeue.
 *
 *   oqueue->remove() removes the first item and returns it.
 *   oqueue->unwind() removes the final item and returns it.
 *
 *   the dequeue is implemented as a bidirectional circular linked list;
 *   an empty dequeue is one item linked to itself in both directions; 
 *   an empty dequeue is detected either by oqueue == oqueue->first()
 *   or oqueue == oqueue->final(); otherwise, members present.
 *
 *   oqueue->IsEmpty() performs this test and returns true or false;
 *
 *   when a new item is added, a oqueue object is created that points  
 *   to it and that object is inserted or appended by swapping pointers
 *   the first and final dequeue objects are always at hand for access;
 *
 *   as a design decision, looking at the first or final object deletes 
 *   it from the dequeue. For example, a stack can be implemented by:
 *
 *   oqueue *list = new oqueue();    ... make list head.
 *   ...
 *   list->first(myobject1);       ... push myobject1 on stack
 *   list->first(myobject2);       ... push myobject2 on stack
 *   ...
 *   myobject1 = list->first();    ... pop myobject2 from stack
 *   myobject2 = list->first();    ... pop myobject1 from stack
 *
 *   if (oqueue->IsEmpty()) { ...}   ... dequeue is empty
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oQUEUE_SOURCE
#define oQUEUE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstddef>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oqueue.hpp"

/*====================================================================*
 *
 *   unsigned oqueue::count() const;
 *
 *   return the number of oqueue objects this dequeue; the number is 
 *   one less than the actual number because empty dequeues have one
 *   member that points to itself in both directions and is not part 
 *   of the dequeue; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

unsigned oqueue::count() const

{
	unsigned counter = 0;
	oqueue * temp = this->mhead;
	while (temp != this)
	{
		temp = temp->mhead;
		counter++;
	}
	return (counter);
}

/*====================================================================*
 *
 *   bool oqueue::empty() const;
 *
 *   return true of the dequeue is empty; the dequeue is empty if
 *   this instance points to itself in either direction; we check
 *   the head pointer for this condition;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

bool oqueue::empty() const

{
	return (this->mhead == this);
}

/*====================================================================*
 *
 *   void * oqueue::data () const;
 *
 *   return a pointer to the object stored in this oqueue instance;  
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

void * oqueue::data() const

{
	return (this->mdata);
}

/*====================================================================*
 *
 *   oqueue *oqueue::head () const;
 *
 *   return a pointer to the next oqueue object in the dequeue; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue * oqueue::head() const

{
	return (this->mhead);
}

/*====================================================================*
 *
 *   oqueue * oqueue::tail () const;
 *
 *   return a pointer to the last oqueue object in the dequeue;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue * oqueue::tail() const

{
	return (this->mtail);
}

/*====================================================================*
 *
 *   oqueue &insert (void * data);
 *
 *   insert an item at the dequeue head position;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::insert(void * data)

{
	oqueue * temp = new oqueue(data);
	temp->mtail = this;
	temp->mhead = this->mhead;
	this->mhead->mtail = temp;
	this->mhead = temp;
	return (* this);
}

/*====================================================================*
 *
 *   oqueue &append (void * data);
 *
 *   insert an item at the dequeue tail position;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::append(void * data)

{
	oqueue * temp = new oqueue(data);
	temp->mhead = this;
	temp->mtail = this->mtail;
	this->mtail->mhead = temp;
	this->mtail = temp;
	return (* this);
}

/*====================================================================*
 *
 *   oqueue &remove ();
 *
 *   remove and discard the first queue item;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::remove()

{
	if (this->mhead != this)
	{
		delete this->mhead;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oqueue &unwind ();
 *
 *   remove and discard the final queue item;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::unwind()

{
	if (this->mtail != this)
	{
		delete this->mtail;
	}
	return (* this);
}

/*====================================================================*
 *
 *   oqueue &attach (oqueue *queue);
 *
 *   Exchange (ie; swap or switch) the prior and after pointers of 
 *   two oqueue objects. This simple operation may be used to split 
 *   one oqueue into two separate queues or merge two queues into 
 *   one.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::attach(oqueue * queue)

{
	oqueue * temp = queue->mhead;
	queue->mhead = this->mhead;
	this->mhead = temp;
	temp = queue->mtail;
	queue->mtail = this->mtail;
	this->mtail = temp;
	return (* queue);
}

/*====================================================================*
 *
 *   oqueue &detach ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::detach()

{
	this->mhead->mtail = this->mtail;
	this->mtail->mhead = this->mhead;
	this->mtail = this;
	this->mhead = this;
	return (* this);
}

/*====================================================================*
 *
 *   oqueue &clear ();
 *
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue & oqueue::clear()

{
	while (this->mhead != this)
	{
		delete this->mhead;
	}
	return (* this);
}

/*====================================================================*
 *
 *   void oqueue ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue::oqueue()

{
	this->mdata = (void *)(0);
	this->mtail = this;
	this->mhead = this;
	return;
}

/*====================================================================*
 *
 *   void oqueue (void * data);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue::oqueue(void * data)

{
	this->mdata = data;
	this->mtail = this;
	this->mhead = this;
	return;
}

/*====================================================================*
 *
 *   void ~oqueue ();
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

oqueue::~ oqueue()

{
	this->mdata = (void *)(0);
	this->mhead->mtail = this->mtail;
	this->mtail->mhead = this->mhead;
	this->mtail = (oqueue *)(0);
	this->mhead = (oqueue *)(0);
	return;
}

/*====================================================================*
 *
 *--------------------------------------------------------------------*/

#endif



