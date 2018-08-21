#include "optCodes.h"
#include "cpuEnums.h"
#include "cpu_core.h"
#include "CounterJumpSize.h"

void nop(cpu * c) {}

void hlt(cpu * c) {
	c->running = false;
}

//Move register to register
void movrtr(cpu * c) {
	int32 dest, src;

	if (c->instruction.first == c->instruction.second) {
		return;
	}

	dest = c->instruction.first;
	src = c->instruction.second;

	if (dest == CPU_REG_NUM::RA_NUM) {
		if (src == CPU_REG_NUM::RB_NUM) {
			c->ra = c->rb;
		}
		else if (src == CPU_REG_NUM::RC_NUM) {
			c->ra = c->rc;
		}
		else if (src == CPU_REG_NUM::RD_NUM) {
			c->ra = c->rd;
		}
	}
	else if (dest == CPU_REG_NUM::RB_NUM) {
		if (src == CPU_REG_NUM::RA_NUM) {
			c->rb = c->ra;
		}
		else if (src == CPU_REG_NUM::RC_NUM) {
			c->rb = c->rc;
		}
		else if (src == CPU_REG_NUM::RD_NUM) {
			c->rb = c->rd;
		}
	}
	else if (dest == CPU_REG_NUM::RC_NUM) {
		if (src == CPU_REG_NUM::RB_NUM) {
			c->rc = c->rb;
		}
		else if (src == CPU_REG_NUM::RA_NUM) {
			c->rc = c->ra;
		}
		else if (src == CPU_REG_NUM::RD_NUM) {
			c->rc = c->rd;
		}
	}
	else if (dest == CPU_REG_NUM::RD_NUM) {
		if (src == CPU_REG_NUM::RB_NUM) {
			c->rd = c->rb;
		}
		else if (src == CPU_REG_NUM::RC_NUM) {
			c->rd = c->rc;
		}
		else if (src == CPU_REG_NUM::RA_NUM) {
			c->rd = c->ra;
		}
	}

}
//Move register to memory
void movrtm(cpu * c) {
	int32 src = c->instruction.first;

	if (src == CPU_REG_NUM::RA_NUM) {
		*(int32*)(c->memory + c->instruction.second) = c->ra;
	}
	else if (src == CPU_REG_NUM::RB_NUM) {
		*(int32*)(c->memory + c->instruction.second) = c->rb;
	}
	else if (src == CPU_REG_NUM::RC_NUM) {
		*(int32*)(c->memory + c->instruction.second) = c->rc;
	}
	else if (src == CPU_REG_NUM::RD_NUM) {
		*(int32*)(c->memory + c->instruction.second) = c->rd;
	}
}
//Move memory to register
void movmtr(cpu * c) {
	int32 dest = c->instruction.third;
	char type = (char)c->instruction.second;

	if (dest == CPU_REG_NUM::RA_NUM) {
		if (type == VAL_TYPE::PTR) {
			c->ra = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::VAL) {
			c->ra = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::PTR_VAL) {
			c->ra = *(int32*)(c->memory + (*(int32*)(c->memory + c->instruction.first)));
		}
		else if (type == VAL_TYPE::ADD_PTR) {
			c->ra = c->instruction.first;
		}
	}
	else if (dest == CPU_REG_NUM::RB_NUM) {
		if (type == VAL_TYPE::PTR) {
			c->rb = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::VAL) {
			c->rb = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::PTR_VAL) {
			c->rb = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::ADD_PTR) {
			c->rb = c->instruction.first;
		}
	}
	else if (dest == CPU_REG_NUM::RC_NUM) {
		if (type == VAL_TYPE::PTR) {
			c->rd = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::VAL) {
			c->rd = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::PTR_VAL) {
			c->rd = *(int32*)(c->memory + (*(int32*)(c->memory + c->instruction.first)));
		}
		else if (type == VAL_TYPE::ADD_PTR) {
			c->rd = c->instruction.first;
		}
	}
	else if (dest == CPU_REG_NUM::RD_NUM) {
		if (type == VAL_TYPE::PTR) {
			c->rc = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::VAL) {
			c->rc = *(int32*)(c->memory + c->instruction.first);
		}
		else if (type == VAL_TYPE::PTR_VAL) {
			c->rc = *(int32*)(c->memory + (*(int32*)(c->memory + c->instruction.first)));
		}
		else if (type == VAL_TYPE::ADD_PTR) {
			c->rc = c->instruction.first;
		}
	}

}
//Move const to register
void movctr(cpu * c) {
	int32 dest = c->instruction.first;

	if (dest == CPU_REG_NUM::RA_NUM) {
		c->ra = c->instruction.second;
	}
	else if (dest == CPU_REG_NUM::RB_NUM) {
		c->rb = c->instruction.second;
	}
	else if (dest == CPU_REG_NUM::RC_NUM) {
		c->rc = c->instruction.second;
	}
	else if (dest == CPU_REG_NUM::RD_NUM) {
		c->rd = c->instruction.second;
	}

}
//Move const to memory
void movctm(cpu * c) {
	*(uint32*)(c->memory + c->instruction.first) = c->instruction.second;
}

//Move register to stack
void movrts(cpu * c) {

	int32 src = c->instruction.first;

	if (src == CPU_REG_NUM::RA_NUM) {
		*(uint32*)(c->stackMemory + (c->stc - c->instruction.second)) = c->ra;
	}
	else if (src == CPU_REG_NUM::RB_NUM) {
		*(uint32*)(c->stackMemory + (c->stc - c->instruction.second)) = c->rb;
	}
	else if (src == CPU_REG_NUM::RC_NUM) {
		*(uint32*)(c->stackMemory + (c->stc - c->instruction.second)) = c->rc;
	}
	else if (src == CPU_REG_NUM::RD_NUM) {
		*(uint32*)(c->stackMemory + (c->stc - c->instruction.second)) = c->rd;
	}

}
//Move stack to register
void movstr(cpu * c) {
	int32 src = c->instruction.second;

	if (src == CPU_REG_NUM::RA_NUM) {
		c->ra = *(uint32*)(c->stackMemory + (c->stc - c->instruction.first));
	}
	else if (src == CPU_REG_NUM::RB_NUM) {
		c->rb = *(uint32*)(c->stackMemory + (c->stc - c->instruction.first));
	}
	else if (src == CPU_REG_NUM::RC_NUM) {
		c->rc = *(uint32*)(c->stackMemory + (c->stc - c->instruction.first));
	}
	else if (src == CPU_REG_NUM::RD_NUM) {
		c->rd = *(uint32*)(c->stackMemory + (c->stc - c->instruction.first));
	}

}

//Stack stuff
void pshreg(cpu * c) {
	int32 src = c->instruction.first;
	if (src == CPU_REG_NUM::RA_NUM) {
		*(uint32*)(c->stackMemory + c->stc) = c->ra;
		c->stc += RegJmp;
	}
	else if (src == CPU_REG_NUM::RB_NUM) {
		*(uint32*)(c->stackMemory + c->stc) = c->ra;
		c->stc += RegJmp;
	}
	else if (src == CPU_REG_NUM::RC_NUM) {
		*(uint32*)(c->stackMemory + c->stc) = c->ra;
		c->stc += RegJmp;
	}
	else if (src == CPU_REG_NUM::RD_NUM) {
		*(uint32*)(c->stackMemory + c->stc) = c->ra;
		c->stc += RegJmp;
	}
	if (c->stc >= c->stackSize) {
		//TODO error check
		//error
	}
}

void pshmem(cpu * c) {
	int32 type = c->instruction.first;
	if (type == VAL_TYPE::PTR) {
		//*(uint32*)(c->stackMemory + c->stc) = *(uint32*)(c->memory + c->instruction.second);
		*(uint32*)(c->stackMemory + c->stc) = c->instruction.second;
		c->stc += MemJmp;
	}
	else if (type == VAL_TYPE::VAL) {
		*(uint32*)(c->stackMemory + c->stc) = *(uint32*)(c->memory + c->instruction.second);
		c->stc += MemJmp;
	}
	else if (type == VAL_TYPE::PTR_VAL) {
		*(uint32*)(c->stackMemory + c->stc) = *(uint32*)(c->memory + c->instruction.second);
		c->stc += MemJmp;
	}
	else if (type == VAL_TYPE::ADD_PTR) {
		*(uint32*)(c->stackMemory + c->stc) = (uint32)c->instruction.second;
		c->stc += MemJmp;
	}
	if (c->stc >= c->stackSize) {
		//TODO error check
		//error
	}
}

void popstk(cpu * c) {
	//we only wanna do this if we have something to remove.
	if (c->stc != 0) {
		c->stc -= MemJmp;
	}
	else {
		//TODO error check
		//error tried poping stack when there was nothing to pop.
	}
}

//MATH STUFF!
void add(cpu * c) {
	c->ra += c->rb;
}
void sub(cpu * c) {
	c->ra -= c->rb;
}
void mul(cpu * c) {
	c->ra *= c->rb;
}

void jmp(cpu * c) {
	c->pc = c->instruction.first;
	//this acounts for the offset jump after each instruction
	c->pc -= offset_table[CPU_OP_CODE::JMP_NOT_EQUAL];
}

void jne(cpu * c) {
	if ((c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL) == CPU_COMPARE_FLAGS::CMP_NOT_EQUAL ) {
		c->pc = c->instruction.first;
		//this acounts for the offset jump after each instruction
		c->pc -= offset_table[CPU_OP_CODE::JMP_NOT_EQUAL];
	}
	
}


void cmprtr(cpu  *c) {
	//Reset our flags
	c->compareFlags = 0;

	int32 dest, src;
	//This is just for making this a litte easyer to read.
	dest = c->instruction.first;
	src = c->instruction.second;

	if (dest == CPU_REG_NUM::RA_NUM) {
		if (src == CPU_REG_NUM::RB_NUM) {
			if (c->ra == c->rb) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->ra != c->rb) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->ra > c->rb) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->ra < c->rb) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
		}
		else if (src == CPU_REG_NUM::RC_NUM) {
			if (c->ra == c->rc) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->ra != c->rc) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->ra > c->rc) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->ra < c->rc) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
		}
		else if (src == CPU_REG_NUM::RD_NUM) {
			if (c->ra == c->rd) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->ra != c->rd) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->ra > c->rd) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->ra < c->rd) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}

		}
	}
	else if (dest == CPU_REG_NUM::RB_NUM) {
		if (src == CPU_REG_NUM::RA_NUM) {
			if (c->rb == c->ra) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rb != c->ra) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rb > c->ra) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rb < c->ra) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}

		}
		else if (src == CPU_REG_NUM::RC_NUM) {
			if (c->rb == c->rc) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rb != c->rc) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rb > c->rc) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rb < c->rc) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
			
		}
		else if (src == CPU_REG_NUM::RD_NUM) {
			if (c->rb == c->rd) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rb != c->rd) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rb > c->rd) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rb < c->rd) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}

		}
	}
	else if (dest == CPU_REG_NUM::RC_NUM) {
		if (src == CPU_REG_NUM::RB_NUM) {
			if (c->rc == c->rb) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rc != c->rb) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rc > c->rb) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rc < c->rb) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
			
		}
		else if (src == CPU_REG_NUM::RD_NUM) {
			if (c->rc == c->rd) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			if (c->rc != c->rd) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rc > c->rd) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rc < c->rd) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}

		}
		else if (src == CPU_REG_NUM::RA_NUM) {
			if (c->rc == c->ra) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rc != c->ra) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rc > c->ra) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rc < c->ra) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
			
		}

	}
	else if (dest == CPU_REG_NUM::RD_NUM) {
		if (src == CPU_REG_NUM::RB_NUM) {
			if (c->rd == c->rb) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rd != c->rb) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rd > c->rb) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rd < c->rb) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
		}
		else if (src == CPU_REG_NUM::RC_NUM) {
			if (c->rd == c->rc) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rd != c->rc) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rd > c->rc) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rd < c->rc) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
			
		}
		else if (src == CPU_REG_NUM::RA_NUM) {
			if (c->rd == c->ra) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
			}
			else if (c->rd != c->ra) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
				if (c->rd > c->ra) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
				}
				else if (c->rd < c->ra) {
					c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
				}
			}
			
		}
	}

}

void cmprtm(cpu  *c) {
	int32 dest, src;
	c->compareFlags = 0;
	dest = c->instruction.first;
	src = c->instruction.second;

	if (dest == CPU_REG_NUM::RA_NUM) {
		if (c->ra == src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->ra != src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->ra > src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->ra < src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}

	}
	else if (dest == CPU_REG_NUM::RB_NUM) {
		if (c->rb == src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->rb != src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->rb > src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->rb < src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}
	}
	else if (dest == CPU_REG_NUM::RC_NUM) {
		if (c->rc == src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->rc != src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->rc > src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->rc < src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}
	}
	else if (dest == CPU_REG_NUM::RD_NUM) {
		if (c->rd == src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->rd != src) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->rd > src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->rd < src) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}
	}

}

void cmprtc(cpu  *c) {
	c->compareFlags = 0;
	int32 dest;
	dest = c->instruction.first;

	if (dest == CPU_REG_NUM::RA_NUM) {
		if (c->ra == (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->ra != (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->ra > (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->ra < (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}
		
	}
	else if (dest == CPU_REG_NUM::RB_NUM) {
		if (c->rb == (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->rb != (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->rb > (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->rb < (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}

	}
	else if (dest == CPU_REG_NUM::RC_NUM) {
		if (c->rc == (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		if (c->rc != (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->rc > (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->rc < (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}


	}
	else if (dest == CPU_REG_NUM::RD_NUM) {
		if (c->rd == (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_EQUAL;
		}
		else if (c->rd != (int32)c->instruction.second) {
			c->compareFlags |= CPU_COMPARE_FLAGS::CMP_NOT_EQUAL;
			if (c->rd > (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_GRATER_THAN;
			}
			else if (c->rd < (int32)c->instruction.second) {
				c->compareFlags |= CPU_COMPARE_FLAGS::CMP_LESS_THAN;
			}
		}
		
	}
}

void RunOpCode(cpu * c) {
	switch (c->instruction.opCode) {
	case CPU_OP_CODE::NO_OP:
		nop(c);
	case CPU_OP_CODE::JMP_TO_MEM:
		jmp(c);
		break;
	case CPU_OP_CODE::JMP_NOT_EQUAL:
		jne(c);
		break;
	case CPU_OP_CODE::ADD_REG_TO_REG:
		add(c);
		break;
	case CPU_OP_CODE::SUB_REG_TO_REG:
		sub(c);
		break;
	case CPU_OP_CODE::MUL_REG_TO_REG:
		mul(c);
		break;
	case CPU_OP_CODE::CMP_REG_TO_REG:
		cmprtr(c);
		break;
	case CPU_OP_CODE::CMP_REG_TO_MEM:
		cmprtm(c);
		break;
	case CPU_OP_CODE::CMP_REG_TO_CON:
		cmprtc(c);
		break;
	case CPU_OP_CODE::MOVE_REG_TO_REG:
		movrtr(c);
		break;
	case CPU_OP_CODE::MOVE_REG_TO_MEM:
		movrtm(c);
		break;
	case CPU_OP_CODE::MOVE_MEM_TO_REG:
		movmtr(c);
		break;
	case CPU_OP_CODE::MOVE_CON_TO_REG:
		movctr(c);
		break;
	case CPU_OP_CODE::MOVE_CON_TO_MEM:
		movctm(c);
		break;
	case CPU_OP_CODE::HALT_CPU:
		hlt(c);
		break;
	default:
		hlt(c);
	}
}