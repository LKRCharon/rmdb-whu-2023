// /* Copyright (c) 2023 Renmin University of China
// RMDB is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//         http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details. */

// #pragma once
// #include <memory>
// #include "execution_defs.h"
// #include "execution_manager.h"
// #include "executor_abstract.h"
// #include "index/ix.h"
// #include "system/sm.h"

// #include "execution/executor_abstract.h"
// #include "record/rm_defs.h"

// class JoinBuffer {
//    public:
//     const static int JOIN_BUFFER_SIZE = 1000;
//     std::unique_ptr<RmRecord> buffer_[JOIN_BUFFER_SIZE];
//     size_t size_;  // 记录大小
//     size_t cur_pos_;

//     JoinBuffer() : size_(0), cur_pos_(0) {}

//     void push_back(std::unique_ptr<RmRecord> record) {
//         assert(!is_full());
//         buffer_[size_] = std::move(record);
//         size_++;
//     }

//     void beginTuple() { cur_pos_ = 0; }

//     void nextTuple() { cur_pos_++; }

//     std::unique_ptr<RmRecord>* get_record() {
//         assert(!is_end());
//         return &buffer_[cur_pos_];
//     }

//     void reset() {
//         memset(buffer_, 0, sizeof(buffer_));
//         cur_pos_ = 0;
//         size_ = 0;
//     }

//     bool is_full() { return size_ >= JOIN_BUFFER_SIZE; }

//     bool is_end() { return cur_pos_ >= size_; }
// };

// class ExecutorWithJoinBuffer {
//    public:
//     std::unique_ptr<AbstractExecutor>* executor_;
//     std::unique_ptr<JoinBuffer> join_buffer_;
//     ExecutorWithJoinBuffer(std::unique_ptr<AbstractExecutor>* exe) : executor_(exe) {
//         join_buffer_ = std::make_unique<JoinBuffer>();
//     }

//     void beginBuffer() {
//         (*executor_)->beginTuple();
//         join_buffer_->reset();
//         while (!(*executor_)->is_end() && !join_buffer_->is_full()) {
//             join_buffer_->push_back(std::move((*executor_)->Next()));
//             (*executor_)->nextTuple();
//         }
//     }

//     void nextBuffer() {
//         assert(!is_end());
//         join_buffer_->reset();
//         while (!(*executor_)->is_end() && !join_buffer_->is_full()) {
//             join_buffer_->push_back(std::move((*executor_)->Next()));
//             (*executor_)->nextTuple();
//         }
//     }

//     std::unique_ptr<JoinBuffer>* Next() {
//         // assert(!is_end());
//         return &join_buffer_;
//     }

//     bool is_end() { return join_buffer_->size_ == 0; }
// };

// class NaiveBlockNestedLoopJoinExecutor : public AbstractExecutor {
//    private:
//     std::unique_ptr<AbstractExecutor> left_;   // 左儿子节点（需要join的表）
//     std::unique_ptr<AbstractExecutor> right_;  // 右儿子节点（需要join的表）
//     size_t len_;                               // join后获得的每条记录的长度
//     std::vector<ColMeta> cols_;                // join后获得的记录的字段

//     std::vector<Condition> fed_conds_;  // join条件
//     bool isend;

//     // join buffer
//     std::unique_ptr<ExecutorWithJoinBuffer> left_blocks_;
//     std::unique_ptr<ExecutorWithJoinBuffer> right_blocks_;
//     std::unique_ptr<JoinBuffer>* left_join_buffer_;
//     std::unique_ptr<JoinBuffer>* right_join_buffer_;

//    public:
//     NaiveBlockNestedLoopJoinExecutor(std::unique_ptr<AbstractExecutor> left, std::unique_ptr<AbstractExecutor> right,
//                                      std::vector<Condition> conds) {
//         left_ = std::move(left);
//         right_ = std::move(right);
//         len_ = left_->tupleLen() + right_->tupleLen();
//         cols_ = left_->cols();
//         auto right_cols = right_->cols();
//         for (auto& col : right_cols) {
//             col.offset += left_->tupleLen();
//         }
//         cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
//         isend = false;
//         fed_conds_ = std::move(conds);

//         // 初始化join buffer
//         left_blocks_ = std::make_unique<ExecutorWithJoinBuffer>(&left_);
//         right_blocks_ = std::make_unique<ExecutorWithJoinBuffer>(&right_);
//     }

//     const std::vector<ColMeta>& cols() const override { return cols_; };

//     bool is_end() const override { return isend; };

//     size_t tupleLen() const override { return len_; };

//     std::string getType() override { return "NaiveNaiveBlockNestedLoopJoinExecutor"; };

//     //
//     void beginTuple() override {
//         // 1. 初始化 left blocks, right blocks, left join buffer, right join buffer
//         left_blocks_->beginBuffer();
//         right_blocks_->beginBuffer();
//         left_join_buffer_ = left_blocks_->Next();
//         right_join_buffer_ = std::move(right_blocks_->Next());
//         (*left_join_buffer_)->beginTuple();
//         (*right_join_buffer_)->beginTuple();
//         // 2. 初始化 isend并开启循环寻找第一个符合要求的节点
//         isend = false;
//         find_next_valid_tuple();
//     }

//     void nextTuple() override {
//         assert(!is_end());
//         // // 1. 移动一位
//         // if(right_->is_end()) {
//         //     left_->nextTuple();
//         //     right_->beginTuple();
//         // }else {
//         //     right_->nextTuple();
//         // }
//         (*right_join_buffer_)->nextTuple();
//         // right_->nextTuple();
//         // 2. 找到下一个合法的tuple
//         find_next_valid_tuple();
//     }

//     std::unique_ptr<RmRecord> Next() override {
//         assert(!is_end());
//         // 1. 取left_record和right_record
//         auto left_record = (*left_join_buffer_)->get_record();
//         auto right_record = (*right_join_buffer_)->get_record();
//         // 2. 合并到一起
//         auto ret = std::make_unique<RmRecord>(len_);
//         memcpy(ret->data, (*left_record)->data, (*left_record)->size);
//         memcpy(ret->data + (*left_record)->size, (*right_record)->data, (*right_record)->size);
//         return ret;
//     }

//     Rid& rid() override { return _abstract_rid; }

//    private:
//     // 找到下一个符合fed_cond的tuple
//     void find_next_valid_tuple() {
//         // 1.开启循环体，四重循环
//         while (!left_blocks_->is_end()) {
//             while (!right_blocks_->is_end()) {
//                 while (!(*left_join_buffer_)->is_end()) {
//                     auto left_record = (*left_join_buffer_)->get_record();
//                     while (!(*right_join_buffer_)->is_end()) {
//                         // 寻找符合条件的tuple
//                         auto right_record = (*right_join_buffer_)->get_record();
//                         // 检查是否符合fed_cond
//                         bool is_fit = true;

//                         auto is_fit = eval(*left_record->data, *right_record->data);
//                         // 如果符合要求，则返回
//                         if (is_fit) {
//                             return;
//                         }
//                         (*right_join_buffer_)->nextTuple();
//                     }
//                     // right_join_buffer_遍历完毕
//                     // left_join_buffer_+1, right_join buffer重新开始遍历
//                     (*left_join_buffer_)->nextTuple();
//                     (*right_join_buffer_)->beginTuple();
//                 }
//                 // left join buffer和right join buffer都遍历完毕
//                 // left join buffer重新开始遍历，right join buffer刷新
//                 (*left_join_buffer_)->beginTuple();
//                 right_blocks_->nextBuffer();
//                 right_join_buffer_ = right_blocks_->Next();
//                 (*right_join_buffer_)->beginTuple();
//             }
//             // right blocks中的所有buffer都遍历过一遍了
//             // left blocks + 1， right blocks重新遍历
//             left_blocks_->nextBuffer();
//             left_join_buffer_ = left_blocks_->Next();
//             (*left_join_buffer_)->beginTuple();
//             right_blocks_->beginBuffer();
//             right_join_buffer_ = right_blocks_->Next();
//             (*right_join_buffer_)->beginTuple();
//         }
//         // 遍历结束，没有符合要求的tuple了
//         isend = true;
//         return;
//     }
// };
