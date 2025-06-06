from itertools import permutations
import copy

queue1 = [1,1]
queue2 = [1,5]

def solution(queue1, queue2):
    answer = -1
    extend_q = []
    extend_q.extend(queue1)
    extend_q.extend(queue2)
    q_sum = sum(queue1) + sum(queue2)
    if (q_sum) % 2 != 0:
        return -1
    target_num = q_sum / 2
    l_list = ['l' for i in queue1]
    l_list.extend('l')
    r_list = ['r' for i in queue2]
    r_list.extend('r')
    extend_lr = []
    extend_lr.extend(l_list)
    extend_lr.extend(r_list)
    lr_list = ['l', 'r']

    lr_set = set()

    my_dict = {0: [] ,1: ["l", "r"]}
    sir = copy.deepcopy(queue1)
    sil = copy.deepcopy(queue2)
    sil_pop = sil.pop(0)
    sir.append(sil_pop)

    sir2 = copy.deepcopy(queue1)
    sil = copy.deepcopy(queue2)
    sir_pop = sir2.pop(0)
    sil.append(sir_pop)
    my_dict_res = {"r": {
            "q1": sir,
            "q2": copy.deepcopy(queue2)[1:]
        },
        "l": {
            "q1": copy.deepcopy(queue1)[1:],
            "q2": sil,
        }
    }

    if sum(queue1) == sum(queue2):
        return 0

    for i in range(len(extend_lr)):
        if i == 0:
            continue
        alp_list = copy.deepcopy(my_dict[i-1])
        for alp in alp_list:
            # l first
            alp_list_l = copy.deepcopy(alp) + "l"
            if i == 1:
                temp_q1 = copy.deepcopy(queue1)
                temp_q2 = copy.deepcopy(queue2)
            else:
                temp_q1 = copy.deepcopy(my_dict_res[alp]["q1"])
                temp_q2 = copy.deepcopy(my_dict_res[alp]["q2"])
            if sum(temp_q1) == sum(temp_q2):
                return i-1
            if len(temp_q1) != 0:
                temp_q2.append(temp_q1.pop(0))
            my_dict_res[alp_list_l] = {"q1": [], "q2": []}
            my_dict_res[alp_list_l]["q1"] = copy.deepcopy(temp_q1)
            my_dict_res[alp_list_l]["q2"] = copy.deepcopy(temp_q2)
            if not my_dict.get(i):
                my_dict[i] = []
            my_dict[i].append(alp_list_l)

            #r
            alp_list_r = copy.deepcopy(alp) + "r"
            if i == 1:
                temp_q1 = copy.deepcopy(queue1)
                temp_q2 = copy.deepcopy(queue2)
            else:
                temp_q1 = copy.deepcopy(my_dict_res[alp]["q1"])
                temp_q2 = copy.deepcopy(my_dict_res[alp]["q2"])
            if sum(temp_q1) == sum(temp_q2):
                return i-1
            if len(temp_q2) != 0:
                temp_q1.append(temp_q2.pop(0))
            my_dict_res[alp_list_r] = {"q1": [], "q2": []}
            my_dict_res[alp_list_r]["q1"] = copy.deepcopy(temp_q1)
            my_dict_res[alp_list_r]["q2"] = copy.deepcopy(temp_q2)
            my_dict[i].append(alp_list_r)
    # print(my_dict)
    # print(sorted(my_dict_res, key=len))
    # print(my_dict_res.items())
    # for key, val in my_dict_res.items():
    #     if key != 7:
    #         continue
    #     print(val)
    return answer


print(solution(queue1, queue2))

